#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#define N 16
#define M 32


//				Calloc (Numero di oggetti , sizeof(oggetto));


//Nodo che contiene l'informazione da elaborare
typedef struct elemento{

	struct elemento *next;
	char *parola; 

}nodo;


typedef struct stuttura_coda{

	pthread_mutex_t mutex;
	pthread_cond_t empty;
	nodo *head;
	nodo *tail;
	int lung;
	int fine;

}queue;

//										--Variabili globali--

queue *q = NULL; 
int val;


//								--funzioni di utilità per la gestione della coda--
queue *creaCoda(){

	queue *q = (queue*) malloc(sizeof(queue));
	if(q == NULL){
		perror("errore calloc in creaCoda");
		exit(EXIT_FAILURE);
	}
	q->head = NULL;
	q->tail = NULL;
	q->lung = 0;
	q->fine = 0;
	if(pthread_mutex_init(&q->mutex , NULL) != 0){
		perror("pthread_mutex_init");
		exit(EXIT_FAILURE);
	}
	if(pthread_cond_init(&q->empty , NULL) != 0){
		perror("pthread_cond_init");
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



//AddNode
void pushNode(char* val , queue *q){

	nodo *new = creaNodo(val);
	pthread_mutex_lock(&q->mutex);

	if(val == NULL || q == NULL){
		perror("errore nella push");
		exit(EXIT_FAILURE);
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
	pthread_mutex_unlock(&q->mutex);

	return estratto;
}

//														--Funzioni semplici di utilità---

void incFine(queue *q){

	pthread_mutex_lock(&q->mutex);
	q->fine++;
	pthread_mutex_unlock(&q->mutex);

}

int checkFine(queue *q){

	pthread_mutex_lock(&q->mutex);
	int x = q->fine;
	pthread_mutex_unlock(&q->mutex);
	return x;
}

int checkLung(queue *q){
	pthread_mutex_lock(&q->mutex);
	int x = q->lung;
	pthread_mutex_unlock(&q->mutex);
	return x;
}

//															--Funzioni Pthread()--


static void *consumatore(void *arg){

//Fino a quando il numero dei thread che hanno inserito qualcosa in coda e sono usciti è minore di N checkFine(q) < N  Or la cosa è non vuota estrai nodi.
//Elimino i nodi passati dalla funzione popNode();
	
	 while(checkFine(q) < N || checkLung(q) > 0){
		nodo *popped = popNode(q);
	 	printf("%s\n",popped->parola);
	 	free(popped->parola);
	 	free(popped);
	 }
	 return (void *) 0;
}

static void *produttore(void *arg){

	 for(int i = 0 ; i < val ; i++){
	 	pushNode("ciao",q);
	 }
	 incFine(q);
	 return (void*) 0;
}

//																	--Main--



int main(int argc , char **argv ){

	pthread_t *tid1 , *tid2;
	tid1 = malloc(N * sizeof(pthread_t));
	tid2 = malloc(M * sizeof(pthread_t));
	if(argc == 1){
		perror("introdurre un intero");
		return -1;
	}
	q = creaCoda();
	int tmp = atoi(argv[1]);
	val = tmp/N;

	for(int i = 0 ; i < N ; i++)	pthread_create(&tid1[i] , NULL , &produttore ,NULL);
	for(int i = 0 ; i < N ; i++) pthread_join(tid1[i] , NULL);
	for(int j = 0 ; j < M ; j++)	pthread_create(&tid2[j] , NULL , &consumatore , NULL);
	for(int j = 0 ; j < M ; j++) pthread_join(tid2[j] , NULL);
	free(tid1);
	free(tid2);
	//Distruggo la coda
	killQueue(q);
	return 0;

}



