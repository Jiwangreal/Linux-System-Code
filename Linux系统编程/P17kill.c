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
        kill(getppid(), SIGUSR1);//向父进程发送SIGUSR1信号
        exit(EXIT_SUCCESS);
    }    
    //防止sleep被信号打断
    //5s的时间被信号中断了，留下的剩余时间4s，再睡眠4s即可
    int n = 5;
    do
    {
        n = sleep(n);
    } while (n > 0);
    
    // sleep(5);//父进程运行一段时间,直接使用sleep，会被信号打断 man 3 sleep
    return 0;
}

void handle(int sig)
{
    printf("recv a sig=%d\n", sig);
}
