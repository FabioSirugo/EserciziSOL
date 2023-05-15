#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc , char ** argv){

	if(argc < 3){
		fprintf(stderr, "Inserisci più argomenti %s FileInLettura e FileInScrittura DimBuffer\n", argv[0]);
		return -1;
	}
	FILE *leggo = NULL;
	FILE *scrivo = NULL;

	const long BuffDim = atoi(argv[3]);

	if((leggo = fopen(argv[1], "r" ) ) == NULL){
		perror("errore in aperture di FileInScrittura");
		exit(EXIT_FAILURE);		//La exit fa terminare il programma.
	}
	//Se arrivo qua vuol dire che fd_leggo è diverso da -1 quindi non ho errore.

	if((scrivo = fopen(argv[2] , "w" ) ) == NULL){
		perror("errore in apertura di FileInScrittura ");
		exit(EXIT_FAILURE);		//La exit fa terminare il programma.	
	}

	char *buf = malloc(BuffDim * sizeof(char));
	//Se arrivo qua vuol dire che fd_scrivo è diverso da -1 quindi non ho errore.

	while(fgets(buf , BuffDim , leggo)){
		if(fprintf(scrivo , "%s" , buf) == -1){ 
			perror("errore in scrittura in FileInScrittura");
			exit(EXIT_FAILURE);
		}
	}

	if(fclose(scrivo) == -1){
		perror("errore in chisura FileInScrittura");
		exit(EXIT_FAILURE);
	}

	if(fclose(leggo) == -1){
		perror("errore in chisura FileInLettura");
		exit(EXIT_FAILURE);	
	}

	free(buf);

	return 0;
}