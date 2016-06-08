#ifndef _COMMANDS_H
#define _COMMANDS_H

#include <sys/types.h>
#include "struct.h"

typedef int (* argumente) (int argc, char** argv, int in, int out);

typedef struct {
    char* nume;
    argumente callback;
} args_callback;



typedef enum {
    DEFAULT,
    STRING
} TYPE;

typedef struct {
    char* nume;
    int in;
    int out;
    int ret;
    int op;   
    lista* args;
    args_callback* fct;
    TYPE tip;
    pid_t pid;
}comanda;

extern lista* comenzi_inregistrate;

comanda* add_comanda();
void free_comanda();
int exec_fct();
int comanda_exista(comanda* fct);
void register_command(char* nume, argumente callback);
args_callback* has_command(char * nume);
int exec_fct(comanda* fct);
void exec_linie(lista* linie);
#endif
