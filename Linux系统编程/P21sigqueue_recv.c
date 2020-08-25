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

void  handler(int, siginfo_t *, void *);

int main(int argc, char *argv[])
{
    struct sigaction act;
    //要想接收数据，得用sa_sigaction
    act.sa_sigaction = handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_SIGINFO;//安装信号接收数据的时候，要用SA_SIGINFO！！否则，不能接收数据

    if (sigaction(SIGINT, &act, NULL) <0)
        ERR_EXIT("sigaction error\n");

    for (;;)
        pause();
    return 0;

}
void  handler(int sig, siginfo_t *info, void *ctx)
{
    //接收的数据在siginfo_t中的si_value中
    //si_value对应的就是联合体union sigval
    //man sigqueue
    //若是整型数据：数据接收还可以用这个字段info->si_int
    //若是指针数据，则用 info->si_ptr字段来接收
    printf("recv a sig = %d date=%d date=%d\n", sig, info->si_value.sival_int,info->si_int);
}




