#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>


void recursiveDir(struct dirent *file , DIR *d){
	if(errno != 0)	recursiveDir(file = readdir(d)  , d);
	printattr(file->d_name);
}




int main(int argc , char **argv){

	if( argc == 1 ){
		fprintf(stderr, "Inserisci %s pathDirectory \n", argv[0]);
		return -1;
	}
	DIR  *direc = NULL;
	struct dirent *file = NULL;
	if( (direc = opendir(argv[1] ) ) == NULL ){
		perror("Errore nell'aprire la directory");
		exit(EXIT_FAILURE);
	}
	recursiveDir(file , direc);

	return 0;
}