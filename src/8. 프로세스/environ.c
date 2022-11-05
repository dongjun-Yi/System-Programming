#include <stdio.h>
#include <stdlib.h>
 
/* 모든 명령줄 인수와 환경 변수를 프린트한다. */
int main(int argc, char *argv[])
{
   char    **ptr;
   extern char  **environ;

   for (ptr = environ; *ptr != 0; ptr++) /* 모든 환경 변수 값 프린트*/
       printf("%s \n", *ptr);

   exit(0);
}
