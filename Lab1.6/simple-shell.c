

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>



#define MAX_LINE		80 /* 80 chars per line, per command */

int main(void)
{
	char buf[MAX_LINE/2 + 1];	/* command line (of 80) has max of 40 arguments */
  int should_run = 1;
  pid_t baby_pid; //Es el indicador para saber si es padre o hijo
  int i=0, upper=0;
 
		
    while (should_run){   
        printf("osh>");
        fflush(stdout);
        fgets(buf,MAX_LINE,stdin);
        
        baby_pid = fork();
        
        
        if(baby_pid<0){
          printf("Error, not a child or a parent\n");
          return 1; //Es un error, se manda 1, si es 0 esta bien        
        }
        else if(baby_pid==0){// proceso de child
          char * x[MAX_LINE]={"/bin/bash","-c",buf};
          execvp(x[0],x);
          return 0; //0 es sin errores
        }
        else if (baby_pid > 0){//proceso de papa
          wait(NULL);
          return 0;
        
        }
        
    }
    
	return 0;
}
