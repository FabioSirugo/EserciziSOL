#include <stdio.h>
#include <stdlib.h>

#define dimN 16
#define dimM  8
												
//In CHECK_PTR controllo X. Se X == NULL Devo evitare che il programma vada avanti quindi devo chiamare Perror(#str) per segnalare il motivo dell'uscita e solo tramite exit(EXIT_FAILURE) arresto il programma.
								
												
#define CHECK_PTR(X, str)	\
    if ((X) ==NULL) {		\
		perror(#str);		\
		exit(EXIT_FAILURE);	\
    }


//Come in Architetture è come se avessi RegistroBaseM + Registroi + Registroj per trovare la locazione in cui scrivere

#define ELEM(M,i,j)	M[(dimM*i) + j]		



//Chiamo un doppio for per scorrere la matrice.									
									
									
#define PRINTMAT(M , dimN , dimM)	\
    for(size_t i=0;i<dimN;++i){		\
		for(size_t j=0;j<dimM;++j)		\
			printf("%ld ",ELEM(M,i,j));	\
		printf("\n");	\
	}



int main() {
	
    long *M = malloc(dimN*dimM*sizeof(long));
    CHECK_PTR(M, "malloc"); 
    for(size_t i=0;i<dimN;++i)
	for(size_t j=0;j<dimM;++j)			
	    ELEM(M,i,j) = i+j;    
    
    PRINTMAT(M, dimN, dimM);

    return 0;
}
