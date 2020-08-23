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
        perror(m);
        exit(EXIT_FAILURE);
    } while(0)
void handle(int sig);


void printsigset(sigset_t *set)
{
    int i;
    for (i = 1; i < NSIG; ++i)//NSIG表示信号的最大值：为64
    {
        if (sigismember(set, i))//检测对应的信号是否在集合中，若在输出1，不在输出0
            putchar('1');
        else
            putchar('0');
    }
    printf("\n");
}

void 
int main(int argc, char *argv[])
{
    sigset_t pset;
    sigset_t bset;
    
    sigemptyset(&bset);
    //增加一个阻塞的信号
    sigaddset(&bset, SIGINT);

    if (signal(SIGINT, handle) == SIG_ERR)
        ERR_EXIT("signal error");

    //改变进程中的信号屏蔽字
    sigprocmask(SIG_BLOCK, &bset, NULL);
    for(;;)
    {
        //man sigpending
        //sigpending:获取进程中未决的信号集保存到pset
        sigpending(&pset);
        printsigset(&pset);
        sleep(1);
    }
    return 0;
}

void handle(int sig)
{
    printf("recv a sig=%d\n", sig);
}
