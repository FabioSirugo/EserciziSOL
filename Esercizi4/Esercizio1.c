#include <stdio.h>
#include <stdlib.h>


#define ELEM(M,i,j)	M[(dimM*i) + j]																
#define PRINTMAT(M , dimM)	            \
    for(size_t i=0;i<dimM;++i)		    \
		for(size_t j=0;j<dimM;++j)		\
			printf("%f",ELEM(M,i,j));	\
	

float *createMatrix(int dimM){

	float *a = malloc((dimM*dimM) * sizeof(float));
	return a;
	
}

float *startMatrix(float *a , int dimM){
	
	int i = 0;
	int j = 0;
	for( i = 0 ; i < dimM ; i++ )
		for( j = 0 ;j < dimM ; j++)
			a[(dimM*i) + j]= (i+j)/2.0;
	
	return a;
}


int main(int argc, char *argv[]) {

	if(argc < 2){
		fprintf(stderr, "Inserire %s ed un valore intero N\n" ,argv[0]);
		return -1;
	}
	
	FILE *matdat;
	FILE *mattxt;
	int dimM = atoi(argv[1]);
	
	//APERTURA DEI FILE
	
	if((matdat = fopen("mat_dump.dat" , "wb")) == NULL){ //fwrite
		perror("fopen di mat_dump.dat fallita");
		exit(EXIT_FAILURE);
  	}

	if((mattxt = fopen("mat_dump.txt" , "w")) == NULL){	//fprintf
		perror("fopen di mat_dump.txt fallita");
		exit(EXIT_FAILURE);
  	}
  	
  	//CREAZIONE MATRICE
  	
	float *m = createMatrix(dimM);
	m = startMatrix(m , dimM);
	
	//INSERISCO LA DIMENSIONE DELLA MATRICE IN TESTA AL FILE
	
	
	int *tmp = &dimM; 
	if(fwrite( tmp , sizeof(int) , 1 , matdat) == 0){			
		perror("Errore nella scrittura del file mat_dumb.dat");
		exit(EXIT_FAILURE);	
	}

	if(!fprintf(mattxt ,"%d\n" ,dimM)){
		perror("Errore nella scrittura del file mat_dumb.txt");
		exit(EXIT_FAILURE);	
	}


	//SCRIVO NEI FILE LE MATRICI
	
	int err = 0;
	int i = 0;
	int dimtot = dimM*dimM;
	
	if(fwrite(m , sizeof(float) , dimM*dimM, matdat) == 0){			
		perror("Errore nella scrittura del file mat_dumb.dat");
		exit(EXIT_FAILURE);	
	}
	
	while(i < dimtot){
		if(i % dimM == dimM-1 )		err = fprintf(mattxt ,"%f\n" ,m[i]);			
		else	err = fprintf(mattxt ,"%f " ,m[i]);
		if(err == 0){			
			perror("Errore nella scrittura del file mat_dumb.txt");
			exit(EXIT_FAILURE);	
		}
		i++;
	}
	
	free(m);
	fclose(mattxt);
	fclose(matdat);

	return 0;

}

