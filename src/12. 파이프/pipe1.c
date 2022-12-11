#include <stdio.h>
#include <string.h>
#include <unistd.h>
#define READ 0	
#define WRITE 1

int main(int argc, char* argv[]) 
{
    char str[1024];
    char *command1, *command2;
    int fd[2];

    printf("$");
    fgets(str,sizeof(str),stdin);
  
    str[strlen(str)-1] ='\0';
    fflush(stdin);

    if(strchr(str,'|') != NULL) {		//파이프 사용하는 경우
        command1 = strtok (str,"| ");
        command2 = strtok (NULL, "| ");
        printf("cmd1 :%s\n cmd2 :%s\n",command1,command2);
        strcat(command1,"\0");
        strcat(command2,"\0");
    } 
 
    pipe(fd);	     			

    if (fork() ==0) {  		
        close(fd[READ]);
	dup2(fd[WRITE],1);
	close(fd[WRITE]);
	execlp(command1, command1, NULL);
	perror("pipe"); 	
    } else {
	close(fd[WRITE]);
	dup2(fd[READ],0);
	close(fd[READ]);
	execlp(command2, command2, NULL);
	perror("pipe"); 
   }
}
