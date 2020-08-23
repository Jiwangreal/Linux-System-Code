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
int main(int argc, char *argv[])
{
    //man alarm
    if (signal(SIGALRM, handle) == SIG_ERR)
        ERR_EXIT("signal error");
    alarm(1);//alarm函数可以指定秒，过了多少秒之后产生一个SIGALRM信号
    for(;;)
        pause();
    return 0;
}

void handle(int sig)
{
    printf("recv a sig=%d\n", sig);
}
