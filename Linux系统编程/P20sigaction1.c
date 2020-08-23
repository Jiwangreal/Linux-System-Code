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

void handler(int sig);
//用sigaction模拟signal函数
_sighandler my_signal(int sig, _sighandler_t handler);

int main(int argc, char *argv[])
{
    // struct sigaction act;
    // act.sa_handler = handler;
    // sigemptyset(&act.sa_mask);
    // act.sa_flags = 0;

    // if (sigaction(SIGINT, &act, NULL) <0)
    //     ERR_EXIT("sigaction error\n");
    
    my_signal(SIGINT, handler);
    for (;;)
        pause();
    return 0;

}

//信号原来的行为从oldact返回回来
//my_signal等价于signal函数
//signal函数既可以安装可靠信号，也可以安装不可靠信号
//但是在安装可靠信号时，函数指针只能是handler，不能用可以传递更多数据的函数
_sighandler my_signal(int sig, _sighandler_t handler)
{
    strucy sigaction act;
    struct  sigaction lodact;
    act.sa_handler = handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    //信号原来的行为从oldact返回回来
    if (sigaction(sig, &act, &oldact) <0)
        return SIG_ERR;

    return oldact.handler;//返回信号原来的处理函数
}


void handler(int sig)
{
    printf("recv a sig = %d\n", sig);
}