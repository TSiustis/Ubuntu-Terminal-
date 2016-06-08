#ifndef _LISTA_H	
#define _LISTA_H
#include <stdio.h>
#include <errno.h>
typedef struct Node* node;

struct Node{
void *data;
node urm,ant;
};

typedef struct{
 node primul;
 node ultimul;
 int counter;
}lista;


lista *list();
void add_lista(lista* list, void* data);
void free_lista();
int  list_is_first(lista* list, node node);
int getword(FILE *fp);
void counter(char* file);
char * concatenare(const char * old, const char * newc);


#endif
