#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <signal.h>


#define ERR_EXIT(m) \
    do \
    { \
        perror(m);  \
        exit(EXIT_FAILURE); \
    } while(0)
void handle(int sig);
int main(int argc, char *argv[])
{
    if (signal(SIGUSR1, handle) == SIG_ERR)
        ERR_EXIT("signal error");

    pid_t pid = fork();
    if (pid == 0)
        ERR_EXIT("fork error");
    if (pid == 0)
    {
        pid = getpgrp();//获取进程组的号码
        kill(-pid, SIGUSR1);

        //上面2行等价于下面的1行代码
        // killpg(getpgrp(), SIGUSR1);
        exit(EXIT_SUCCESS);
    }    

    int n = 5;
    do
    {
        n = sleep(n);
    } while (n > 0);
    
    return 0;
}

void handle(int sig)
{
    printf("recv a sig=%d\n", sig);
}
