#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc , char ** argv){

	if(argc < 3){
		fprintf(stderr, "Inserisci più argomenti %s FileInLettura e FileInScrittura DimBuffer\n", argv[0]);
		return -1;
	}

	const long BuffDim = atoi(argv[3]);
	int fd_leggo = 0;
	int fd_scrivo = 0;

	if((fd_leggo = open(argv[1],O_RDONLY))== -1){
		perror("errore in aperture di FileInScrittura");
		exit(EXIT_FAILURE);		//La exit fa terminare il programma.
	}
	//Se arrivo qua vuol dire che fd_leggo è diverso da -1 quindi non ho errore.

	if((fd_scrivo = open(argv[2] , O_WRONLY | O_CREAT , 0666 ))==-1){
		perror("errore in apertura di FileInScrittura ");
		exit(EXIT_FAILURE);		//La exit fa terminare il programma.	
	}

	int valRead = 0;
	int valWrite = 0;
	char *buf = malloc(BuffDim * sizeof(char));
	//Se arrivo qua vuol dire che fd_scrivo è diverso da -1 quindi non ho errore.

	while((valRead = read(fd_leggo , buf , BuffDim)) > 0){
		if((valWrite = write(fd_scrivo, buf , valRead)) == -1){ //Se mettessi write(1 , buf , BuffDim) indentificherei il fd dello stdout 
			perror("errore in scrittura in FileInScrittura");
			exit(EXIT_FAILURE);
		} 
	}
	if(valRead == -1){
		perror("errore in lettura di FileInLettura");
		exit(EXIT_FAILURE);	
	}
	
	if(close(fd_scrivo) == -1){
		perror("errore in chisura FileInScrittura");
		exit(EXIT_FAILURE);
	}

	if(close(fd_leggo) == -1){
		perror("errore in chisura FileInLettura");
		exit(EXIT_FAILURE);	
	}

	free(buf);
	
	return 0;
}