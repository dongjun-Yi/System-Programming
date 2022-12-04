#include <stdio.h>
#include <unistd.h>
#include <signal.h>

struct sigaction newact;
struct sigaction oldact;
void sigint_handler(int signo);

int main( void)
{
   newact.sa_handler = sigint_handler; // 시그널 처리기 지정
   sigfillset(&newact.sa_mask);         // 모든 시그널 봉쇄 
                                           
   // SIGINT를 지정하면서 oldact에 기존 처리기 정보를 저장한다.   
   sigaction( SIGINT, &newact, &oldact); 
   while(1 )
   {
       printf( "Ctrl-C 를 눌러 보세요 !\n");
       sleep(1);
   }
}

void sigint_handler(int signo)
{
   printf( "%d 번 시그널 처리!\n", signo);
   printf( "또 누르면 종료됩니다.\n");
   sigaction(SIGINT, &oldact, NULL);
}


