#include  <sys/types.h>  
#include  <sys/wait.h>
#include  <errno.h>
#include  <unistd.h>

int mysystem(const char *cmdstring) 
{
    int pid, status;

    if (cmdstring == NULL)   /* 명령어가 NULL인 경우 */
        return 1;

    pid = fork();
    if (pid == -1)           /* 프로세스 생성 실패 */
        return -1;

    if (pid == 0) {
        execl("/bin/sh", "sh", "-c", cmdstring, (char *) 0);
        _exit(127);          /* 명령어 실행 오류 */
    }

    do {
        if (waitpid(pid, &status, 0) == -1) {
            if (errno != EINTR) /* waitpid()로부터 EINTR 오류 외 */ 
                return -1;
        } else return status;
    } while(1);
}
