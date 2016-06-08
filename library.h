#ifndef CMD_H
#define	CMD_H

#include "commmands.h"
#include <stdio.h>
#define COUNT(c)       \
           ccount++;        \
           if ((c) == '\n') \
             lcount++;

#define openf() FILE *fdout = stdout, *fdin = stdin;                 \
    if (out != STDOUT_FILENO) fdout = fdopen (out, "a"); else fdout = stdout; \
    if (in != STDIN_FILENO) fdin = fdopen(out, "r"); else fdin = stdin;

#define closef() if (out != STDOUT_FILENO) fclose (fdout); if (in != STDIN_FILENO) fclose(fdin);

#define print(...) fprintf(fdout,__VA_ARGS__)
#define scan(...)  fscanf(fdin, __VA_ARGS__)
 int ccount;
     int wcount;
     int lcount;
void inregistrare_comenzi();


#endif	
