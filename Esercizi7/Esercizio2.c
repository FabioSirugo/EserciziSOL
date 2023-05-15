#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void printInode(struct stat fileStat){
	printf("File Inode Number : %ld\n",fileStat.st_ino);
	printf("File Inode Mode : ");
	printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");	//Se è una directory stampa "d" else "-"
    printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");	
    printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
    printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
    printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");
    printf("\n");
	printf("File Inode UderId: %d\n",fileStat.st_uid);
	printf("File Inode GroupId: %d\n",fileStat.st_gid);
	printf("File Inode last time modif: %ld\n",fileStat.st_ctime);
	printf("\n");
}


int main(int argc , char ** argv){

	if(argc == 1){
		fprintf(stderr, "Inserisci più argomenti %s File1 File2 File3 ecc...\n", argv[0]);
		return -1;
	}

	struct stat fileStat;			//Struct che mi permette di accedere all'Inode del file (o directory) su cui ho eseguito la open.
	int fd = 0;
	int i = 1;

	while(argv[i]!= NULL){

	//Apro File con solo permessi di lettura		

		if((fd = open(argv[i],O_RDONLY))== -1){
			perror("errore in aperture di FileInScrittura");
			exit(EXIT_FAILURE);		//La exit fa terminare il programma.
		}

	//Inizializzo o per meglio dire istanzio la struttura utilizzando il file descriptor del file corrente su cui ho fatto la open	
		if(fstat(fd , &fileStat) < 0)	return 1;	

		printf("File Inode name : %s\n",argv[i]);
		printInode(fileStat);
		i++;
	}

	return 0;
}