#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *reverse(char *string){

	int dims = strlen(string);	//strlen non considera il carattere terminatore.
	char *new = malloc((1 + dims));	//Aggiungo 1 per considerare anche '\0'.
	new[dims] = '\0';  // alla locazione dims aggiungo il carattere terminatore.
	int i = 0;
	int j = dims-1;

	for (i = 0; i < dims; i++) {
	      new[i] = string[j];
	      j--;
	}
	
	return new;
}


int main(int argc, char *argv[]){
	
	FILE *inf = NULL;
	FILE *outf = NULL;
	char *leggo = NULL;
	char *temp = NULL;
	char *stato = NULL;
	char *buf = malloc(1024 * sizeof(char));

	if(argc >= 2){
		if((inf = fopen(argv[1],"r")) == NULL){
			perror("Errore aprendo il file in lettura\n");
			return -1;
		}
		if((outf = fopen(argv[2] , "w")) == NULL){
			perror("Errore aprendo il file in scrittura\n");
			return -1;
		}
		while(fgets(buf , 1024 , inf)){
			buf[strlen(buf)-1] = '\0';
			leggo = strtok(buf, " ");
			while(leggo){
				temp = reverse(leggo);
				puts(temp);
				leggo = strtok(NULL, " ");
				fprintf(outf , "%s\n" , temp);
				free(temp);
			}
		}
	}
	free(buf);
	fclose(inf);
	fclose(outf);				
	return 0;
}
	
/*
ciao ragazzi
ciao ragazze
come state
*/











