#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printMatrix(float *a ,  int dim){

	int dimTot = dim * dim;
	int i = 0;
	while(i < dimTot){
		if(i % dim == dim-1)		printf("%f\n",a[i]);			
		else	printf("%f ",a[i]);	
		i++;
	}		
}

float *getMatrixtxt(FILE *leggitxt , int dim){
	int dimTot = dim * dim;
	float *a = malloc(dimTot * sizeof(float));
	int i = 0;
	while(i < dimTot){
		fscanf(leggitxt , "%f" ,&a[i]);
		i++;
	}

	return a;

}

float *getMatrixdat(FILE *leggidat , int dim){

	int dimTot = dim * dim;
	float *a = malloc(dimTot*sizeof(float));
	int i = 0;
	while(i < dimTot){
		fread(&a[i] ,sizeof(float) , 1 , leggidat);	
		i++;
	}

	return a;

}


//Confronta è una funzione che prende come primo parametro una funzione , come secondo parametro un float m1 terzo un float m2 ed un int 
//l'idea è quella di far eseguire a Confronta una fuonzione dentro di se.

int Confronta(int (*compare)(const void *s1 , const void *s2 , size_t n) , float *m1 , float *m2 , int dim){
	return compare(m1 , m2 , dim);	
}


int main(int argc, char *argv[]) {

	if(argc < 3){
		fprintf(stderr, "Inserire %s e 2 file in lettura <file1.txt> <file2.dat> \n" ,argv[0]);
		return -1;
	}

	printf("Per comodità passo la dimensione della matrice con i file in input , mettendo nella prima riga del file la dimensione dim\n");	
	FILE *leggitxt = NULL;
	FILE *leggidat = NULL;
	
	float *mat1 = NULL;
	float *mat2 = NULL;
	
	//Apertura dei file in lettura.
	
	if((leggitxt = fopen(argv[1] , "r")) == NULL){ 
		perror("fopen di mat_dump.txt fallita");
		exit(EXIT_FAILURE);
  	}
  	
	if((leggidat = fopen(argv[2] , "r")) == NULL){ 
		perror("fopen di mat_dump.dat fallita");
		exit(EXIT_FAILURE);
  	}
  	
  	//Estrazione dimensione matrici.
  	
  	int dim = 0;
  	if(!fscanf(leggitxt , "%d" , &dim)){
		perror("lettura di mat_dump.txt fallita");
		exit(EXIT_FAILURE);  	
  	}

 	if(!fread(&dim ,sizeof(int) , 1 , leggidat)){
		perror("lettura di mat_dump.dat fallita");
		exit(EXIT_FAILURE);  	
  	}
 	
	int dimTot = dim*dim;	
  	printf("Dimensione matrice %d * %d\n" , dim , dim);
	printf("ok\n");
	
	mat1 = getMatrixtxt(leggitxt ,  dim);
	printMatrix(mat1 , dim);
	printf("ok\n");

	mat2 = getMatrixdat(leggidat , dim);	
	printMatrix(mat2 , dim);
	
	printf("%d\n",Confronta(memcmp , mat1 , mat2 , dimTot ));


	free(mat1);
	free(mat2);
	fclose(leggitxt);
	fclose(leggidat);

	return 0;
	
}
