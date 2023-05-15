#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(int argc , char **argv){

	if(argc == 1){
		fprintf(stderr , "Avvia in questo modo : %s inserisci un numero \n" , argv[0]);
		return -1;
	}

	long time = atol(argv[1]); 
	int pid = 0;
	printf("Inizio\n");
	if((pid = fork()) == -1) {
		perror("Main : Errore nella fork");
		exit(EXIT_FAILURE);
	}

	//Figlio
	if(pid == 0){
		//printf("FIGLIO\n");
		printf("Processo figlio %d dorme per %ld secondi mio padre è %d \n", getpid(), time , getppid());
		sleep(time);
	}

	//Padre
	if( pid ){
		int val = 0;
		printf("Processo padre %d attende che il Figlio termini \n", getpid());
		//Con waitpid(-1 , NULL , 0) attendo che finisca un processo figlio qualsiasi senza salvare lo stato.
		if((val = waitpid(-1 , NULL , 0)) == -1){		
			perror("Errore nel waitpid");
		}
	}

	return 0;
}