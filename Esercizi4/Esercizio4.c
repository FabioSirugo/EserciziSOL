#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void checkWL(char **argv ,int argc , int *lflag , int *wflag){

	int c;
	while ((c = getopt (argc, argv, "lw")) != -1){			//Parsa tutti gli elementi passati dalla line di comando e controlla se 
		switch (c)											//se -l -w sono presenti.
		{
		  case 'l':
		    *lflag = 1;
		    break;
		  case 'w':
		    *wflag = 1;
		    break;
		}
	}
}

int countW(FILE *inf){

	char *buf = malloc(2000);
	int count = 0;
	int linew = 1;
	int i = 0;

//con questo algoritmo non considero mai l'ultima parola quindi inizializzo linew = 1 contando appunto l'ultima parola.
//Alloco una stringa di (2000 char) con fgets nel buffer buf... Una volta ottenuta la stringa controllo gli spazi per spezzare le parole

	while(fgets(buf , 1024 , inf) != NULL){
		linew = 1;		
		//ciclo sul buffer cercando gli spazi
		//dopo aver contato le parole in una riga salvo il risultato in linew
		for (i = 0 ; buf[i] != '\0' ; i++)		if(buf[i] == ' ')	count++;
		count+= linew;
	}

	free(buf);								//libero il buffer 
	rewind(inf);							// " riavvolgo " il file

	return count;							//ritorno il numero di parole

}

int countL(FILE *inf){

	int count = 0;
	char *buf = malloc(1024);

	while(fgets(buf , 1024 , inf) != NULL)	count++;		
				
	rewind(inf);							// " riavvolgo " il file
	return count;
}

int main(int argc , char *argv[]){

	if(argc == 1){
		fprintf(stderr, "Inserire %s -l -w +file di testo \n" ,argv[0]);
		return -1;
	}
	int lflag = 0;
	int wflag = 0;	
	checkWL(argv ,argc , &lflag , &wflag);
	int i = 1;
	i+=wflag+lflag;
	FILE *leggo =NULL;

	while(i < argc){
	
//controllo che il file venga aperto correttamente
		
		if((leggo = fopen(argv[i] , "r")) == NULL){
			fprintf(stderr ,"Errore apertura file o comandi inseriti male.\nInserire -l -w e non %s\n",argv[i]);
			return -1;		
		}

		if((lflag && wflag) || (!lflag && !wflag))printf("Il numero di parole ed il numero di righe del file %s sono : %d   %d\n",argv[i] , countW(leggo) , countL(leggo));
		if(lflag && !wflag)	printf("Il numero di righe del file %s sono : %d\n",argv[i] , countL(leggo));
		if(!lflag && wflag)	printf("Il numero di parole del file %s sono : %d\n",argv[i] , countW(leggo));

//chiudo il file aperto

		fclose(leggo);
		i++;
	}

	return 0;
}

