#include "structura.h"
#include "library.h"
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int total_ccount,total_wcount,total_lcount;
int getword (FILE *fp)
     {
       int c;
       int word = 0;
       if(fp==NULL){
       printf("Error %s",strerror(errno));
         return;
         }
      while ((c = getc (fp)) != EOF)
         {
           if (isalpha(c))
             {
               wcount++;
               break;
             }
           COUNT (c);
         }
     
     for (; c != EOF; c = getc (fp))
        {
         COUNT (c);
        if (!isalpha(c))
          break;
         }
  return c!=EOF;
}
void counter (char *file)
     {
       FILE *fp = fopen (file, "r");
       
       if (!fp)
           return;     

       ccount = wcount = lcount = 0;
       while (getword (fp))
         ;
       fclose (fp);
     
       
       total_ccount += ccount;
       total_wcount += wcount;
       total_lcount += lcount;
     }
lista * list(){
lista * aux = (lista*)malloc(sizeof(lista));
aux->primul = NULL;
aux->ultimul=NULL;
aux->counter = 0;

return aux;

}


void add_lista(lista* list, void * data)	
{
    node aux =  (node)malloc(sizeof(struct Node));
    aux->data = data;
    
    if (list->ultimul) {
        aux->ant = list->ultimul;
        list->ultimul->urm = aux;
        list->ultimul = aux;
    } else {
        aux->ant = NULL;
        aux->urm = NULL;
        list->primul = aux;
        list->ultimul = aux;
    }
    
    list->counter++;
}


int list_is_first(lista* list, node nod) {
    if (list->primul == nod) {
        return 1;
    }
    return 0;
}


void free_lista(lista* list)
{
    node current,urm;
    for (current = list->primul; current != NULL; current = urm) {
        urm = current->urm;
        free(current);
    }
}


char * concatenare(const char * old, const char * newc)
{
    size_t len = strlen(old) + strlen(newc) + 2;
    char *out = malloc(len);
    sprintf(out, "%s/%s", old, newc);
    return out;
}
