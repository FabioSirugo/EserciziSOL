#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#define N 10
#include <pthread.h>


// Compilare con gcc -g -Wall -pedantic test1.c -o test1 -lpthread


typedef struct el{

	struct el *next;
	int info;

}nodo;

pthread_mutex_t mtx;
pthread_cond_t cond;

static nodo *head = NULL;

nodo *newNode(){

	srand(time(NULL));
	int r = rand();
	sleep(1);
	nodo *new = malloc(sizeof(nodo));
	new->next = NULL;
	new->info = r;

	return new;

}


void aggiungi(nodo *new){


	if(head == NULL)	head = new;
	else{
		nodo *tmp = head;
		while(tmp->next != NULL){
			tmp = tmp->next;
		}
		tmp->next = new;
	}
}

nodo *estrai(){

	nodo *tmp = head;
	head = head->next;
	return tmp;

}
void consuma(nodo *p){
	printf("%d\n",p->info);
}



//												--Produttore--
//Non ho bisogno di utilizzare la lock immediatamente , la utilizzo solo poco prima di usare qualche variabile condivisa
//In questo uso la lock prima di aggiungere P al buffer , quindi devo necessariamente usare la mutua esculusione.
//Dopo aver aggiunto il valore eseguo la signal

static void *produttore(void * arg){
	nodo *p = NULL;
		for(int i = 0 ; i < N ; i++){
			p = newNode();
			pthread_mutex_lock(&mtx);
//			printf("LockAcquire del Produttore\n");
			aggiungi(p);

//	Utilizzando la signal in questo punto ogni volta che produco un messaggio lo scheduler manda in exec il thread consumatore
//	In poche parole fa un colpo uno ed un colpo un altro.

			pthread_cond_signal(&cond);
//			printf("LockRealise del Produttore\n");
			pthread_mutex_unlock(&mtx);
		}	

//	pthread_cond_signal(&cond); usando la signal in questo punto il consumatore si attiverebbe solo dopo che 
//	il produttore ha riempito il buffer!

	return (void*) 0;
}


//										--Consumatore--
//Il consumatore esegue un 
//
//


static void *consumatore(void * arg){
	nodo *p;
	while(1){
		pthread_mutex_lock(&mtx);
//	printf("LockAcquire del Consumatore\n");
		while(head == NULL)		pthread_cond_wait(&cond , &mtx);
		p = estrai();
//		printf("LockRealise del Consumatore\n");
		pthread_mutex_unlock(&mtx);
		consuma(p);
		free(p);
	}

	return(void*) 0;
}



int main(void){

	pthread_t tid1 , tid2;
	int status1 , status2;
	pthread_create(&tid1 , NULL , &produttore , NULL);
	pthread_create(&tid2 , NULL , &consumatore , NULL);
	sleep(20);
	pthread_join(tid1 , (void*) &status1);
	pthread_cancel(tid2);
	pthread_join(tid2 , (void*) &status2);
	return 0;
}