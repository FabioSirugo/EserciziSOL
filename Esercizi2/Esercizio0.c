#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
 
    if (argc != 3) {
		fprintf(stderr, "use: %s stringa1 stringa2\n", argv[0]);
		return -1;
    }
 
    char *stato1 = NULL;
    char *stato2 = NULL;
    char* token1 = (char *) malloc(strlen(argv[1]) *sizeof(char));
    char* token2 = (char *) malloc(strlen(argv[2]) *sizeof(char));
    
    token1 = strcpy(token1 , argv[1]);
	token2 = strcpy(token2 , argv[2]);
    char* token11 = strtok_r(token1 , " " , &stato1);

    while(token11){
		printf("%s\n", token11);
		token2 = strcpy(token2 , argv[2]);
		char *token12 = strtok_r(token2 , " " , &stato2);
		while(token12) {
		    printf("%s\n", token12);
		    token12 = strtok_r(NULL, " " , &stato2);
		}
		token11 = strtok_r(stato1, " " , &stato1);
    }
    return 0;
}
