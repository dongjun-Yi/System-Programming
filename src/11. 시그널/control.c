#include <stdio.h>
#include <unistd.h>
#include <signal.h>

/* 시그널을 이용하여 자식 프로세스들을 제어한다. */
int main( )
{
   int pid1, pid2, count1 = 0, count2 = 0;

   pid1 = fork( );
   if (pid1 == 0) {
      while (1) {
         sleep(1);
         printf("자식[1] 실행: %d\n", ++count1);
      }
   }

   pid2 = fork( );
   if (pid2 == 0) {
      while (1) {
         sleep(1);
         printf("자식[2] 실행: %d\n", ++count2);
      }
   }

   sleep(3);
   kill(pid1, SIGSTOP);
   sleep(3);
   kill(pid1, SIGCONT);
   sleep(3);
   kill(pid2, SIGSTOP);
   sleep(3);
   kill(pid2, SIGCONT);
   sleep(3);
   kill(pid1, SIGKILL);
   kill(pid2, SIGKILL);
}
