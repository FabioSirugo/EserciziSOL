#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*	
	Static variables in C have the lifetime of the program. If defined in a function, they have local scope, i.e. they can be accessed only 	inside those functions. The value of static variables is preserved between function calls. In the below program, sum is stored in the 		data segment.
int somma_r(int x , int *x){

	sum = INIT_VALUE;		//valore iniziale sum == 100.
	sum += x;
	return sum;



}

*/




//Non è rientrante.


int somma(int x){

	// sum viene inizializzata dal compilatore con un comando speciale. Essendo statica essa possiede un suo stato e non viene deallocata 
	// dallo stack, in questo modo è in grado di mantenere lo stato interno nella funzione somma anche in chiamate successive.           
	//Questa funzione non è rientrante... Un altro thread potrebbe accedere alla variabile sum e modificarne il contenuto.

	static int sum = INIT_VALUE;		//valore iniziale sum == 100.
	sum += x;
	return sum;

}


int main(int argc, char *argv[]) {
    
    //Controllo che vi sia passato 1 argomento dalla line di comando.
    
    if (argc < 2) {
		fprintf(stderr, "Inserisci più argomenti %s FileInLettura \n", argv[0]);
		return -1;
	}   
    FILE *inf = NULL;
    
    //Controllo che il file sia aperto correttamente altrimenti errore.
    
	if((inf = fopen(argv[1],"r")) == NULL){
		perror("Errore aprendo il file in lettura\n");
		return -1;
	}

	char *buf = malloc(1024);
	while(fgets(buf , 1024 , inf))			somma(atoi(buf));
	printf("La somma è %d\n" , somma(0));
	int chiusuraFile;

	//Controllo nella chiusura del file.

	if((chiusuraFile = fclose(inf)) != 0){
		fprintf(stderr , "File chiuso in modo scorretto\n");
		return -1;
	}
	
	return 0;
}
