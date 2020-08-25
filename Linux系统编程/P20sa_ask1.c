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

void handler(int sig);

int main(int argc, char *argv[])
{
    //当处理函数在执行的过程中，加入到掩码中的信号将要被阻塞
    struct sigaction act;
    act.sa_handler = handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;


    //将SIGINT加入到了进程中的信号屏蔽字，将对应的位置为1
    //SIGINT信号发生的时候，不能被递达，会处于pending未决状态
    sigset_t s;
    sigemptyset(&s);
    sigaddset(&s, SIGINT);
    sigprocmask(SIG_BLOCK, &s, NULL);

    if (sigaction(SIGINT, &act, NULL) <0)
        ERR_EXIT("sigaction error\n");

    for (;;)
        pause();
    return 0;

}
void handler(int sig)
{
    printf("recv a sig = %d\n", sig);
}




