#include "commands.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <signal.h>
#include <sys/stat.h> 
#include "struct.h"

lista* comenzi_inregistrate;


void inregistrare_comanda(char* nume, argumente callback)
{
    if (comenzi_inregistrate == NULL) {
        comenzi_inregistrate = list();
    }
    
    args_callback* comanda= (args_callback*) malloc(sizeof(args_callback));
    comanda->nume = strdup(nume);
    comanda->callback = callback;
    
    add_lista(comenzi_inregistrate, (void *) comanda);
}


args_callback* has_command(char * nume) {
    node aux = comenzi_inregistrate->primul;
    while (aux) {
        args_callback* comanda = aux->data;
        if (strcmp(comanda->nume, nume) == 0) {
            return comanda;
        }
        aux = aux->urm;
    }
    
    return NULL;
}


comanda* add_comanda() 
{
    comanda* cmd = (comanda*) malloc(sizeof(comanda));
    cmd->ret = -1;
    cmd->op = -1;
    cmd->tip = DEFAULT;
    cmd->in = STDIN_FILENO;
    cmd->out = STDOUT_FILENO;
    
    return cmd;
}


void free_comanda(comanda* fct) 
{
    if (fct != NULL) {
        if (fct->nume) {
            free(fct->nume);
        }
        free_lista(fct->args);
        free(fct);
    }
}

comanda* to_cmd(node cmd_ptr)
{
    return (comanda*) cmd_ptr->data;
}


int comanda_exista(comanda* fct) {
    char* env = strdup(getenv("PATH"));
    char* path = strtok(env, ":");
    struct stat sb;
   if (fct->fct != NULL) {
        return 1;
    }
    while (path) {
        char* fct_path = concatenare(path, fct->nume);
        if ((stat(fct_path, &sb) == 0) && (sb.st_mode & S_IXOTH)) {
            return 1;
        }
        path = strtok(NULL, ":");
    }
    return 0;
}

char** prepare_args(lista* list, int* n)
{
   int argc = 0;
   char ** args;
   
   args = malloc((list->counter + 1) * sizeof(char*));
   
   node nod = list->primul;
   
   while (nod != NULL) {
       char* arg = (char*) nod->data;
       args[argc++] = strdup(arg);
       nod = nod->urm;
   }
   
   args[argc] = NULL;
   *n = argc;

   return args;
}



int exec_fct(comanda* fct)
{
    pid_t ret = -1;
    char ** args;
    int argc = 0;

    args = prepare_args(fct->args, &argc);

    if (fct->fct != NULL) {
        fct->ret = ret = fct->fct->callback(argc, args, fct->in, fct->out);
        fct->ret = ret; 
    } else {
        ret = fork();
        if (ret == 0) {
            dup2(fct->in, STDIN_FILENO);
            dup2(fct->out, STDOUT_FILENO);
            execvp(fct->nume, args);
        } else {
            wait(NULL);
        }
    }
    return ret;
}

void exec_linie(lista* line)
{
    node cmd_ptr = line->primul;

    int current_in = dup(STDIN_FILENO);
    
    while (cmd_ptr != NULL) {
        comanda* fct = (comanda*) cmd_ptr->data;
        if (fct->tip!= STRING && ! comanda_exista(fct)) {
            printf("%s: command not found !\n", fct->nume);
            return;
        }
        
        switch (fct->op) {
            case 0: {
                int r, fd[2];
               
                while(cmd_ptr != NULL) {
                    comanda* curr_cmd = (comanda*) cmd_ptr->data;
                    if (curr_cmd->tip != STRING && ! comanda_exista(curr_cmd)) {
                        printf("%s: command not found !\n", curr_cmd->nume);
                        return;
                    }
                    
                    pipe(fd);
                    r = fork();

                    if (r == 0) {
                        close(fd[0]);
                        curr_cmd->in = current_in;
                        if (cmd_ptr->urm != NULL) {
                            if (curr_cmd->op == 1) { 
                                int file = open(to_cmd(cmd_ptr->urm)->nume, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR);

                                if (file < 0) {
                                    printf("Error occurred while writing to file via redirect !\n");
                                    return;
                                }
                                curr_cmd->out = file;
                            } else { 
                                curr_cmd->out = fd[1];
                            }
                        }
                        exec_fct(curr_cmd);

                        close(fd[1]);
                        exit(0);
                    } else {
                        wait(NULL);
                        close(fd[1]);
                        current_in = fd[0];
                    }
                    
                    cmd_ptr = cmd_ptr->urm;
                }
                
                if (cmd_ptr == NULL) {
                    return;
                }
            }
            break;
            case 1: {
                node next_cmd_ptr = cmd_ptr->urm;
                comanda* next_cmd = (comanda*) next_cmd_ptr->data;
                    
                if (next_cmd_ptr != NULL) {
                    int file = open(next_cmd->nume, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR);
                    
                    if (file < 0) {
                        printf("Error occurred while writing to file via redirect !\n");
                        return;
                    }
                    fct->out = file;
                    exec_fct(fct);
                    close(file);
                }
            }
            break;
            default: {
                exec_fct(fct);
                break;
            }
        }
        
        cmd_ptr = cmd_ptr->urm;
    }
}
