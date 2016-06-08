#include "library.h"
#include "struct.h"
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <getopt.h>
#include <sys/utsname.h>
#include <ftw.h>
#include <errno.h>    
     int total_ccount = 0;
     int total_wcount = 0;
     int total_lcount = 0;

int cmd_version(int argc, char** argv, int in, int out)
{
    openf();
    struct utsname un;
    uname(&un);
    print("Terminal\n");
    print("Author: Siustis Teodor\n");
    print("System: %s\n", un.version);
    print("Running on %s processor !\n", un.machine);
    closef();
    return 0;
}


int cmd_help(int argc, char** argv, int in, int out)
{  
    openf();
    int i = 0, found = 0;
    static char* text[] = {
        "wc: wc\nafiseaza numarul de cuvinte, newline-uri si byte size al unui fisier",
        "tee: tescrie text intr-un fise\nier!",
        "yes: yes\nafiseaza un text pana la apasarea CTRL-Z",
        "clear: clear\n Goleste ecranul",
        "exit: exit \n Inchide terminalul",
    };
    
    for (i = 0; i < 5; i++) {
        if (argc == 1) {
            print("* %s\n", text[i]);
        } else if (argc > 1 && strstr(text[i], argv[1]) != NULL) {
            print("* %s\n", text[i]);
            found = 1;
            break;
        }
    }
    
    if (argc > 1 && ! found) {
        print("Help for command `%s` not found !\n", argv[0]);
    }
    
    closef();
    return 0;
}



void tee(int argc, char** argv, int in, int out) {
    int i,option =0,location;
   openf();
    if(strcmp(argv[i],"tee")==0) {
       if(strcmp(argv[i+1],"-a")==0){
        option = 1;
        location = i+2;
     }
       location = i+1;
      }     
    
      
    if(option == 0){
    
    	FILE* file = argv[location]? fopen(argv[location],"w"): NULL;
    	if(argv[location] && !file)
    		fprintf(stderr,"cannot open  file \"%s\"\n",argv[1]);
    	char* ch;
    	for(i = location+1;i<argc;i++)
    			fprintf(file,"%s ",argv[i]);
    		
    			fflush(stdout);
    			if(file)
    				fflush(file);
    		
    	
    	
    	if(file)
    		fclose(file);
    	

}
else{
FILE* file = argv[location]? fopen(argv[location],"a"): NULL;
    	if(argv[location] && !file)
    		fprintf(stderr,"cannot open  file \"%s\"\n",argv[2]);
    	char* ch;
    	for(i = location+1;i<argc;i++)
    	    fprintf(file,"%s ",argv[i]);
    		
    			fflush(stdout);
    			if(file)
    				fflush(file);
    		
    	
    	
    	if(file)
    		fclose(file);
    	
    
}
closef();
}
int cmd_wc(int argc, char** argv, int in, int out)
{
  openf();
  
   int i,cntr = 0,ok=1;
int c;
       if (argc < 2)
         printf("usage: wc FILE [FILE...]");
      for (i = 1; i < argc; i++){
         counter(argv[i]);
        }
        
      

     while ((c = getopt(argc, argv, "-c-w-l-L")) != -1){
     switch(c){
     case 'c':{
             printf("Bytes: %d ",total_ccount);
             ok = 0;
             }
            break;
     case 'w':{
              printf("Words: %d ",total_wcount);              
              ok = 0;
             } 
             break;
     case 'l':
            {
             printf("Newlines: %d ",total_lcount);
            ok=0;
            }
            break;
     case '?':printf("Unknown command");
              
             break;
     default:
             break;
    }
} 
    printf("\n");
    if(ok==1)
    printf ("Newlines: %d Words: %d Bytes: %d\n", total_lcount, total_wcount, total_ccount);


closef();
}

  
  





int cmd_yes(int argc,char**argv,int in, int out){
  openf(); 
  char* repeat;
  int i,ok=1;


for(i = 0;i<argc;i++){
   if(strcmp(argv[i],"yes")==0){
     if(argv[i+1]!=NULL)
       repeat = argv[i+1];
   else 
     ok =0;
} 
}
 if(ok==0){
  
  while (1 )
    {
     printf("y\n");
    }
}
else if(ok == 1)
  while(1){
    printf("%s\n",repeat);
}
closef();
return 0;

}


int cmd_exit(int argc, char** argv, int in, int out)
{
    exit(0);
    return 0;
}

int cmd_clear(int argc, char** argv, int in, int out)
{
    system("clear");
    return 0;
}

void inregistrare_comenzi()
{
    
    inregistrare_comanda("tee",tee);
    inregistrare_comanda("wc", cmd_wc);
    inregistrare_comanda("clear1", cmd_clear);
    inregistrare_comanda("version", cmd_version);
    inregistrare_comanda("exit", cmd_exit);
    inregistrare_comanda("help", cmd_help);
    inregistrare_comanda("yes",cmd_yes);
    
}
