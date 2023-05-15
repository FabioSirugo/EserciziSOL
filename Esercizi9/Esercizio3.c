#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#define N 128
#define MAXDIM 2048
//													-- Strutture utilizzate --

typedef struct parole_uniche{

	struct parole_uniche *next;
	char *info;
	int occorrenza;

}unique_word;


//Nodo che contiene l'informazione da elaborare
typedef struct elemento{

	struct elemento *next;
	char *parola; 

}nodo;


typedef struct stuttura_coda{

	pthread_mutex_t mutex;
	pthread_cond_t empty;
	pthread_cond_t full;
	nodo *head;
	nodo *tail;
	int size;
	int lung;
}queue;

//														-- Variabili Globali --


queue *q1 = NULL;
queue *q2 = NULL;


//														-- FUNZIONI --



void stampaUniche(unique_word *head){

	unique_word *tmp = head;
	while(tmp != NULL){
		if(tmp->occorrenza == 1) printf("%s\n",tmp->info);
		tmp = tmp->next;
	}
}

unique_word *inserisci(unique_word *head , char *parola){
	
	int trovato = 1;
	unique_word *tmp = head;
	unique_word *prec = NULL;
	if(head == NULL){
		unique_word *new = malloc(sizeof(unique_word));
		new->occorrenza = 1;
		new->info = malloc(strlen(parola)+1);
		strcpy(new->info , parola);
		new->next = NULL;
		head = new;
		return head;
	}
	else{
		while(tmp != NULL && trovato){
			if(strcmp(parola , tmp->info) == 0){
				tmp->occorrenza++;
				trovato = 0;
			}
			else{
				prec = tmp;
				tmp = tmp->next;
			}
		}
		if(trovato){
			unique_word *new = malloc(sizeof(unique_word));
			new->occorrenza = 1;
			new->info = malloc(strlen(parola)+1);
			strcpy(new->info , parola);
			new->next = NULL;
			prec->next = new;
		}
	}
	return head;
}


queue *creaCoda(int dim){

	queue *q = (queue*) malloc(sizeof(queue));
	if(q == NULL){
		perror("errore calloc in creaCoda");
		exit(EXIT_FAILURE);
	}
	q->head = NULL;
	q->tail = NULL;
	q->lung = 0;
	q->size = dim;
	if(pthread_mutex_init(&q->mutex , NULL) != 0){
		perror("pthread_mutex_init");
		exit(EXIT_FAILURE);
	}
	if(pthread_cond_init(&q->empty , NULL) != 0){
		perror("pthread_cond_init : empty");
		exit(EXIT_FAILURE);
	}
	if(pthread_cond_init(&q->full , NULL) != 0){
		perror("pthread_cond_init : full");
		exit(EXIT_FAILURE);
	}
	return q;
}


//Pointer della coda da cui parte la lista
nodo *creaNodo(char *val){

	nodo *new = (nodo*) malloc(sizeof(nodo));
	if(new == NULL){
		perror("Errore nella malloc : creaNodo");
		exit(EXIT_FAILURE);
	}
	new->next = NULL;
	int lunghezza = strlen(val)+1;
	new->parola = (char*) malloc(lunghezza * sizeof(char));
	if(new->parola == NULL){
		perror("Errore nella malloc : creaNodo");
		exit(EXIT_FAILURE);
	}
	strcpy(new->parola , val);
	return new;
}


//AddNode
void pushNode(char* val , queue *q){

	nodo *new = creaNodo(val);
	pthread_mutex_lock(&q->mutex);

	if(val == NULL || q == NULL){
		perror("errore nella push");
		exit(EXIT_FAILURE);
	}

	while(q->lung == q->size){
		printf("La coda è piena in wait sulla pushNode\n");
		pthread_cond_wait(&q->full , &q->mutex);
	}

	if(q->lung == 0){
		q->head = new;
		q->tail = new;
	}
	else{
		q->tail->next = new;
		q->tail = new;
	}
	q->lung++;
	pthread_cond_signal(&q->empty);
	pthread_mutex_unlock(&q->mutex);

}



//Estrae il nodo
nodo *popNode(queue *q){

	nodo *estratto = NULL; 
	pthread_mutex_lock(&q->mutex);
	while(q->lung == 0){
		printf("La coda è vuota in wait sulla pop\n");
		pthread_cond_wait(&q->empty , &q->mutex);
	}
	if(q->head == NULL){
		perror("Valore non valido : popNode");
		exit(EXIT_FAILURE);
	}

	estratto = q->head;
	q->head = q->head->next;
	q->lung--;
	
	if(q->lung == 0){
		q->tail = NULL;
		q->head = NULL;
	}

	pthread_cond_signal(&q->full);
	pthread_mutex_unlock(&q->mutex);

	return estratto;
}


//Leggo dal file riga per riga... Passo le righe al thread2.
//Una volta terminata la trasmissione di valori passo un carattere non printabile (\n) per far si che lo stage successivo capisca che non deve più attendere niente
//insomma la trasmissione è terminata. Così posso concludere anche il thread1 che appunto termina con successo.
//In ogni riga tolgo \n ed inserisco \0.


static void *stage1(void *arg){

	printf("Thread per la lettura avviato : stage1\n");
	char *buffer = malloc(MAXDIM * sizeof(char));
	int readd = 0;
	if(buffer == NULL){
		perror("Errore nella malloc stage1 buffer");
		exit(EXIT_FAILURE);
	}
	char* val = (char *) arg;
	FILE *file = NULL;
	if((file = fopen(val, "r" )) == NULL){
		perror("errore in aperture di File in lettura");
		exit(EXIT_FAILURE);		//La exit fa terminare il programma.
	}
	while(fgets(buffer , MAXDIM , file)){
		readd = strlen(buffer)-1;
		buffer[readd]= '\0';
		pushNode(buffer , q1);
	}
	free(buffer);
	pushNode("\n" , q1);
	fclose(file);
	printf("Fine stage1\n");
	
	return (void*) 0;

}



//Funzione che tokenizza e manda le stringhe splittate alla coda *q mettere spazi sul test case
void sendToken(char *buffer , queue *q){

	char *token;
	char *stato = NULL;
	token = strtok_r(buffer , " " ,&stato);
	while(token){
		pushNode(token , q);
		token = strtok_r(NULL , " " ,&stato);
	}
	free(token);
}



//Nello stage2 il thread legge all'infinito all'interno della coda1 fino a quando becca la stringa non printabile...
//Una volta incontrato il carattere viene eseguito un break per uscire dal ciclo.
//Arriva correttamente a stampare Fine
// i leak di memoria presenti tra thread2 / thread3 a causa di sendToken.

static void *stage2(void *arg){

	printf("Thread tokenizza avviato : stage2\n");
	nodo *popped = NULL;
	while(1){
		popped = popNode(q1);
		if(popped->parola[0] =='\n'){
			sendToken(popped->parola , q2);
			free(popped->parola);
			free(popped);
			break;
		}
		sendToken(popped->parola , q2);
		free(popped->parola);
		free(popped);
	}
	printf("Fine stage2\n");
	return (void*) 0;
}



//Lo stage3 attende le parole tokenizzate dal thread2 (stage2) e le inserisce in una collezione unique_word dove tramite le funzioni inserisci() e stampaUniche() 
//vengono stampate le perole uniche
//tuttavia abbiamo un problema perchè il thread3 resta in attesa nella pop

unique_word *killList(unique_word *head){

	while(head !=NULL){
		unique_word *tmp = head;
		head = head->next;
		free(tmp->info);
		free(tmp); 
	}
	return head;

}


static void *stage3(void *arg){

	printf("Thread per la selezione della parole uniche avviato : stage3\n");
	unique_word *collection = NULL;
	while(1){
		nodo *popped = NULL;
		popped = popNode(q2);
		if(popped->parola[0] =='\n'){
			free(popped->parola);
			free(popped);
			break;
		}
		collection = inserisci(collection , popped->parola);
		free(popped->parola);
		free(popped);
	}
	stampaUniche(collection);
	collection = killList(collection);
	return (void*) 0;
}


void killQueue(queue *q){

	pthread_mutex_lock(&q->mutex);
	while(q->head != NULL){
		nodo *tempo = NULL;
		tempo = q->head;
		q->head = q->head->next; 
		free(tempo->parola);
		free(tempo);
	}
	pthread_mutex_unlock(&q->mutex);
	free(q);
} 

//Problema nello stage3

int main(int argc , char **argv ){

	if(argc == 1){
		perror("introdurre un file in lettura");
		return -1;
	}
	q1 = creaCoda(N);
	q2 = creaCoda(N);

	pthread_t tid1 , tid2 , tid3;

	pthread_create(&tid1 , NULL , &stage1 , argv[1]);
	pthread_create(&tid2 , NULL , &stage2 , NULL);
	pthread_create(&tid3 , NULL , &stage3 , NULL);


	pthread_join(tid1 , NULL);
	pthread_join(tid2 , NULL);
	pthread_join(tid3 , NULL);
	killQueue(q1);
	killQueue(q2);
	return 0;

}