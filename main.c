#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "library.h"
#include "parser.h"
#include <readline/readline.h>
#include <readline/history.h>

   
  
int main()
{
    char* text;

    inregistrare_comenzi();
    
    while (1) {
        text = readline("$>");
        if ( !text)
            break;

        if (strlen(text) > 0) {
            add_history(text);
        }

        lista* cmd_line = preia_linie(text);
        exec_linie(cmd_line);
        
        free(text);
        
    }
    return 0;
}
