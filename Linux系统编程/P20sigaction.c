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

int main(int argc, char *argv[])
{
    struct sigaction act;
    act.sa_handler = handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    //NULL表示不关心信号之前的行为
    //sigaction关联一个动作
    if (sigaction(SIGINT, &act, NULL) <0)
        ERR_EXIT("sigaction error\n");
    
    //以便有机会发送信号
    for (;;)
        pause();
    return 0;

}
void handler(int sig)
{
    printf("recv a sig = %d\n", sig);
}