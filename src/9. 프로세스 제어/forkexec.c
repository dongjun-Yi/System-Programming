#include <stdlib.h>

#include <stdio.h>

int main()

{

    int pid;

    
    printf("1: pid %d \n", getpid());

    pid = fork(); 

    if (pid == 0) 

	    printf("2: pid %d \n", getpid() ); 

	else execl("/bin/echo", "echo", "3: 100", NULL);


    pid = fork();

    if (pid == 0) 

        printf("4: pid %d \n", getpid() ); 

	else execl("/bin/echo", "echo", "5: 101", NULL);

}
