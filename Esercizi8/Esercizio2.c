#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

//Funzione che genera N processi zombie
//La funzione viene chiamata nel processo figlio dal main
//Esegue un ciclo for in cui vengono eseguite delle fork.....
//I processi figli vengono subito uccisi nella riga if(newpid == 0) exit(getpid());
//nel main viene eseguita una sleep per dare il tempo di controllare i processi Zombie.


void CreaZombie(long i){

	pid_t newpid;
	for(int j = 0 ; j < i ; j++){
		if ( ( newpid = fork() ) == -1) {
			perror("Errore fork in funzione CreaZombie");
			exit(EXIT_FAILURE); 
		}
		if(newpid == 0) exit(getpid());
	}
}



int main(int argc , char **argv){

	pid_t pid;
	long i = 0;

	if(argc == 1){
		perror("inserire un argomento da linea di comando");
		exit(EXIT_FAILURE);
	}

	printf("Inizio\n");
	i = atol(argv[1]);

	if ( ( pid = fork() ) == -1) {
		perror("main fork iniziale: fork");
		exit(EXIT_FAILURE); 
	}
	if ( pid ) {  /* padre */
		sleep(10);
	}
	else { /* figlio */
		CreaZombie(i);
		sleep(10);
	}

	return 0;
}