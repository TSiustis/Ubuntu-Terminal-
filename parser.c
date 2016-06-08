#include <string.h>
#include "commands.h"
#include <stdio.h>
#include <stdlib.h>
#include "parser.h"

int last = 0;

//Redirect : 1 Pipe : 0
int rdpipe(char op) 
{
    switch (op) {
        case '|':
            return 0;
        case '>':
        case '<':
            return 1;
    }
    return -1;
}

comanda* ultima_comanda(lista* list)
{
  if(list->ultimul)
    return (comanda*)list->ultimul->data;
  return NULL;
  
  
}



lista* preia_linie(char *line) 
{
    lista* cmd_list = list();
    int option = 0;
    int last = -1;
    
    char* token = strtok(line, " \t");
    while (token) {
        node last_cmd_node = cmd_list->ultimul;
        
        if (rdpipe(token[0]) != -1) {
            if ( ! cmd_list->ultimul) {
                printf("Operatorii nu trebuie  sa preceada comenzile!\n");
                break;
            } else {
                   if(rdpipe(token[0])==0){
                   ultima_comanda(cmd_list)->op = 0;
                   last = 2;
                }
                if (rdpipe(token[0]) == 1) {
                   ultima_comanda(cmd_list)->op = 1;
                   last = 3;
                }
                option = 0;
            }
        } else if (token[0] == '-' || last == 0) {
            if (last_cmd_node != NULL) {
                add_lista(ultima_comanda(cmd_list)->args, strdup(token));
                option = 1;
                last = 1;
            } else {
                printf("Invalid command syntax: Args should not precede commands!\n");
                break;
            }
        }else {
            if (last == 1) {
                
                add_lista(ultima_comanda(cmd_list)->args, strdup(token));
                last = 1;
            } else {
                comanda* cmd = add_comanda();
                cmd->nume = strdup(token);
                cmd->fct = has_command(token);
                cmd->args = list();
                if (last == 3) {
                    cmd->tip = STRING;
                }
                add_lista(cmd->args, strdup(token));
                add_lista(cmd_list, cmd);
                last = 0;
            }
        }
        token = strtok(NULL, " \t");
    }

    return cmd_list;
}
