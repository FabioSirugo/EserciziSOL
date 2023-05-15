#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 
#define RIALLOCA(buf, newsize) \
	buf = realloc(buf , newsize)
 
char* mystrcat(char *buf, size_t sz, char *first, ...) {
	va_list ap;											//pointer alla lista
	va_start(ap , first);								//inizializzo il primo elemento della lista			
	char *temp = first;									//Variabile temporania per salvare l'elemento estratto dalla lista
	RIALLOCA(buf ,(strlen(temp) + sz));					//Rialloco lo spazio per la stringa in buf
	buf = strcat(buf , temp);							//concateno vecchia e nuova stringa
	while(temp != NULL){							//Ciclo in cui estraggo le stringhe dalla lista
		temp = va_arg(ap , char*);						//Estraggo la stringa
		if(temp != NULL){
		RIALLOCA(buf ,((strlen(temp)+strlen(buf))+1));	//Realloc aggiungento dim stringa vecchia + nuova + 1 per il carattere terminatatore 
		buf = strcat(buf , temp);						//concateno vecchia e nuova stringa
		}
	}
	va_end(ap);											//chiudo la lista ap
	return buf;
}  
 
int main(int argc, char *argv[]) {
  if (argc != 7) { printf("troppi pochi argomenti\n"); return -1; }
  char *buffer=NULL;
  RIALLOCA(buffer, 16); 					    		//Macro che effettua l'allocazione
  buffer[0]='\0';
  buffer = mystrcat(buffer, 16, argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], NULL);
  printf("%s\n", buffer);     
  free(buffer);

  return 0;
}
