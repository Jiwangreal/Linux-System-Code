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

void  handler(int);

int main(int argc, char *argv[])
{
    struct sigaction act;
    act.sa_handler = handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    //对这两个信号进行阻塞
    sigset_t s;
    sigemptyset(&s);
    sigaddset(&s, SIGINT);
    sigaddset(&s, SIGRTMIN);
    sigprocmask(SIG_BLOCK, &s, NULL);

    //安装一个不可靠信号
    if (sigaction(SIGINT, &act, NULL) <0)
        ERR_EXIT("sigaction error\n");

    //安装一个可靠信号
    if (sigaction(SIGRTMIN, &act, NULL) <0)
        ERR_EXIT("sigaction error\n");

    //用来解除阻塞的信号
    if (sigaction(SIGUSR1, &act, NULL) <0)
        ERR_EXIT("sigaction error\n");

    for (;;)
        pause();
    return 0;

}
void  handler(int sig)
{
    if (sig == SIGINT || sig == SIGRTMIN)
        printf("recv a sig = %d", sig);
    else if (sig == SIGUSR1)
    {
        //解除阻塞
        sigset_t s;
        sigemptyset(&s);
        sigaddset(&s, SIGINT);
        sigaddset(&s, SIGRTMIN);
        sigprocmask(SIG_UNBLOCK, &s, NULL);
    }
}




