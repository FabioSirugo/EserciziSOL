#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/* 
 * Calcola ricorsivamente il numero di Fibonacci dell'argomento 'n'.
 * La soluzione deve forkare un nuovo processo che esegue una sola 
 * chiamata di 'doFib'.
 * Se doPrint e' 1 allora la funzione lo stampa, altrimenti il
 * numero calcolato va passato al processo padre.
 */
static void doFib(int n, int doPrint){




}

int main(int argc, char *argv[]) {
    // questo programma puo' calcolare i numeri di Fibonacci solo fino a 13.  
    const int NMAX=13;
    int arg;
    
    if(argc != 2){
        fprintf(stderr, "Usage: %s <num>\n", argv[0]);
        return EXIT_FAILURE;
    }
    arg = atoi(argv[1]);
    if(arg < 0 || arg > NMAX){
        fprintf(stderr, "num deve essere compreso tra 0 e 13\n");
        return EXIT_FAILURE;
    }
    doFib(arg, 1);
    return 0;
}