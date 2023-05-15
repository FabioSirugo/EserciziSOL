list_t *createList();                         // crea una lista vuota   
int     destroyList(list_t *L);               // libera tutta la memoria allocata dalla lista
int     insertList(list_t *L, const char *);  // inserisce una parola nella lista
void    printList(list_t *L);                 // stampa tutta la lista
