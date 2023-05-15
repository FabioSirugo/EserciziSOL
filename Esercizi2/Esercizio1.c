#include <stdio.h>
#include <stdlib.h>
#define N 1000
#define K 10

int main(int argc, char *argv[]) {
	
	float *a = malloc(K*sizeof(float));
	unsigned int seed = time(NULL); // rand_r() utilizza come parametro seme per salvare lo stato dell'ultimo valore ottenuto.
	int i = 0;
	int j = 0; 	
	
	for(i = 0 ; i < K ; i++)	a[i] = 0;

	while(j != N){
		a[rand_r(&seed)%10]++;		//utilizzo l'indirizzo di seme così ricordo lo stato in seme.
		j++;
	}
	
	for(i = 0 ; i < K ; i++){
		a[i] = a[i] / 10;
		printf("%d : %f % \n", i ,a[i]);
	}
	
	free(a);
	return 0;
}
