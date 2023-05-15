#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void myCat(char *file){

	int fd = 0;
	int valRead = 0;
	if((fd = open(file,O_RDONLY))== -1){
		perror("errore in aperture File");
		exit(EXIT_FAILURE);		//La exit fa terminare il programma.
	}
	char *buf = malloc(2048 * sizeof(char));
	if(buf == NULL){
		perror("errore nella malloc");
		exit(EXIT_FAILURE);
	}
	while((valRead = read(fd , buf , 2048)) > 0){
		printf("%s\n", buf);
	}
	if(valRead == -1){
		perror("errore in lettura di file");
		exit(EXIT_FAILURE);	
	}
	if(close(fd) == -1){
		perror("errore in chisura del file");
		exit(EXIT_FAILURE);
	}
	free(buf);
}


int main(int argc , char **argv){

	if(argc == 1){
		fprintf(stderr, "Inserisci più argomenti %s File1.txt File2.txt ... ecc\n", argv[0]);
		return -1;
	}
	for(int i = 1 ; i < argc ; i++){
		myCat(argv[i]);
	}

	return 0;
}