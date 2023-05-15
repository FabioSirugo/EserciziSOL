#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

//La funzione CreaFamiglia esegue un ciclo for in cui vengono generati esattamente N processi.
//Il for controlla che la fork venga eseguita correttamente , se il processo è un processo padre allora questo si mette in attesa e
//aspetta che il figlio termini.
//Una volta terminato il processo figlio , il processo padre esegue una exit(getpid());
//NOTA BENE : quando un processo resta in attesa il valore della i non viene aggiornato da altri processi poichè  
//ogni processo ha la propria i nella propria PCB! Non avviene come con i thread.
//Questo significa che se non chiamassi la exit(getpid()); il processo andrebbe avanti col ciclo for.
//Altra cosa , 
void CreaFamiglia(int n){

	pid_t pid;
	int i = 0;
	for(i = 0 ; i < n ; i++){
		if ( ( pid = fork() ) == -1) {
			perror("Errore in CreaFamiglia: fork");
			exit(EXIT_FAILURE); 
		}
		if(pid > 0){
			printf("%d : creo un processo figlio\n" ,(int) getpid());
			waitpid(-1 , NULL , 0);
			printf("%d : terminato con successo\n" , (int) getpid());
			exit(getpid());
		}
	}
	exit(getpid());
}

int main(int argc , char **argv){
	int n = 0;

	if(argc == 1){
		perror("inserire più argomenti da linea di comando");
		exit(EXIT_FAILURE);
	}
	n = atoi(argv[1]);
	CreaFamiglia(n);

	return 0;
}