#include "tokenizer.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void tokenizer_r(char *arg1 , char *arg2){

	char *stato1 = NULL;
    char *stato2 = NULL;
    char* token1 = (char *) malloc(strlen(arg1) *sizeof(char));
    char* token2 = (char *) malloc(strlen(arg2) *sizeof(char));
    
    token1 = strcpy(token1 , arg1);
	token2 = strcpy(token2 , arg2);
    char* token11 = strtok_r(token1 , " " , &stato1);

    while(token11){
		printf("%s\n", token11);
		token2 = strcpy(token2 , arg2);
		char *token12 = strtok_r(token2 , " " , &stato2);
		while(token12) {
		    printf("%s\n", token12);
		    token12 = strtok_r(NULL, " " , &stato2);
		}
		token11 = strtok_r(stato1, " " , &stato1);
    }

}

void tokenizer(char *arg1 , char *arg2){
	
	char* token1 = strtok(arg1, " ");
	
    while (token1) {
		printf("%s\n", token1);
		char* token2 = strtok(arg2, " ");
		while(token2){
			printf("%s\n", token2);
			token2 = strtok(NULL, " ");
		}
		token1 = strtok(NULL, " ");
    }
    
}
