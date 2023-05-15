#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int getN(char *s2 , int *parametro){

	int esito = 0;
	int valn = 0;
	
	if(s2 != NULL){
		if(strcmp(s2 , "-n") != 0 && strcmp(s2 , "-m") != 0 && strcmp(s2 , "-h") != 0 && strcmp(s2 , "-s") != 0){
			valn = atoi(s2);
			printf("-n %d ",valn);
			esito = 1;
		}
		else  *parametro = 0;
	}
	else printf(" parametro NULL ");
	
	return esito;
}	

int getS(char *s2 , int *parametro){	

	int esito = 0;
		
	if(s2 != NULL){
		printf("-s %s ",s2);
		esito = 1;	
		return esito;
	}
	else printf(" parametro NULL ");

	return esito;

}

int getM(char *s2 , int *parametro){

	int esito = 0;
	int valm = 0;
	
	if(s2 != NULL){
		if(strcmp(s2 , "-n") != 0 && strcmp(s2 , "-m") != 0 && strcmp(s2 , "-h") != 0 && strcmp(s2 , "-s") != 0){
			valm = atoi(s2);
			printf("-m %d ",valm);
			esito = 1;
		}
		else  *parametro = 0;
	}
	else printf(" parametro NULL ");

	
	return esito;
}	
	
void getH(){
	printf("-h nome-programma -n <numero> -s <stringa> -m <numero> ");
}


int main(int argc, char *argv[]) {
	
	int i = 1;
	int esito = 0;
	char *temp = NULL;
	int j = 0;
	int parametro = 1;
	while(i < argc){
		parametro = 1;
		temp = argv[i];
		j = 0;
		while(temp[j] != '\0'){
			if(temp[j] == '-' && temp[j+1] == 'n' && temp[j+2] == '\0') esito = getN(argv[i+1] , &parametro);
			if(temp[j] == '-' && temp[j+1] == 'm' && temp[j+2] == '\0') esito = getM(argv[i+1] , &parametro);
			if(temp[j] == '-' && temp[j+1] == 's' && temp[j+2] == '\0') esito = getS(argv[i+1] , &parametro);
			if(temp[j] == '-' && temp[j+1] == 'h' && temp[j+2] == '\0') getH();
			if(temp[j] == '-' && temp[j+1] != 'h' && temp[j+1] != 'n' && temp[j+1] != 's' && temp[j+1] != 'm' && temp[j+2] == '\0') printf(" Operazione non riconosciuta ");			
			j++;
		}
		if(esito)	i+=2;
		else i++;
		if(!parametro)		printf(" errore parametro ");
	}
	printf("\n");
	return 0;
}		

