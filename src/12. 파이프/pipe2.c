#include <stdio.h>
#include <unistd.h>
#define READ 0	
#define WRITE 1

main(int argc, char* argv[]) 
{
    int fd[2];

    pipe(fd);	     			

    if (fork() ==0) {  		
        close(fd[READ]);
	dup2(fd[WRITE],1);
	close(fd[WRITE]);
	execlp(argv[1], argv[1], NULL);
	perror("Connect"); 	
    } else {
	close(fd[WRITE]);
	dup2(fd[READ],0);
	close(fd[READ]);
	execlp(argv[2], argv[2], NULL);
	perror("Connect"); 
  }
}
