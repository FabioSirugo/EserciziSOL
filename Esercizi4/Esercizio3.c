#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Element{

	char *parola;
	struct  Element *next;

}node_t;

typedef struct Val{
	int n_elem;
	node_t *head;
	
}list_t;


// crea una lista vuota

list_t *createList(){			

	list_t *list = malloc(sizeof(list_t));
	list->head = NULL;
	list->n_elem = 0;
	return list;	
}   


// libera tutta la memoria allocata dalla lista funzione ricorsiva che arriva alla fine e dealloca

int destroyList(list_t *testa){
	if(testa->head != NULL){
		printf("%s\n",testa->head->parola);
		destroyList(testa->head->next); //modificare il tipo
	} 
	free(testa->head->parola);
	free(testa->head);
	return 0;
}


// stampa tutta la lista
void printList(list_t *testa){
	node_t *curr = testa->head;

	while(curr->next!=NULL){
		printf("%s\n" ,curr->parola);
		curr = curr->next;
	}
}


// inserisce una parola nella lista in modo ordinato.
int insertList(list_t *testa, const char *c){

	node_t *curr = testa->head;
	node_t *new = NULL;
	node_t *old = NULL;
	new = malloc(sizeof(node_t));
	new->parola = malloc(strlen(c)+1);
	strcpy(new->parola , c);
	new->next = NULL;
	
	if(testa->head == NULL){
		testa->head = new;			//se la lista è vuota inserisco in testa
		testa->n_elem++;
		return 0;
	}

	while(curr != NULL){
		if(strcmp(curr->parola , new->parola) <= 0){
			old = curr;			//cerco la posizione corretta per inserire il nodo.
			curr = curr->next;
			printf("ok\n");
		}
		else{	
			if(testa->head == curr){		
				new->next = curr;
				curr->next = new;
				testa->n_elem++;
				return 0;
			}
			else{
				old->next = new;
				new->next = curr;
				testa->n_elem++;
				return 0;
			}
		}
	}
	if(testa->head == NULL)	printf("porcodio\n");
	if(curr == NULL)		old->next = new;
	return 0;
}


int main(int argc, char *argv[]) {
/*
	if (argc != 2) {
		fprintf(stderr, "use: %s stringa1 stringa2\n", argv[0]);
		return -1;
    }

	FILE *inp = NULL;
	if(fopen(argv[1],"r") == NULL){
		perror("Errore apertura File");
		return-1;
	}
*/	
	list_t *testa = createList();	
	int i = 0;
	char *val = 0;
	while(i != 4){
		val = malloc(100 *sizeof(char));
		scanf("%s",val);
		insertList(testa ,val);
		i++;
		printf("%d va bene\n" , i );
	}
	printf("\n");
//	printList(testa);
	if(testa->head->next != NULL) destroyList(testa);
	free(testa);
	return 0;

}


/*
list_t *createList();                         // crea una lista vuota   
int   destroyList(list_t *L);               // libera tutta la memoria allocata dalla lista
list_t   insertList(list_t *L, const char *);  // inserisce una parola nella lista
void  printList(list_t *L);                 // stampa tutta la lista
*/
