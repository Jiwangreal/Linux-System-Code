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
    //SIGINT对应键盘ctrl c
    //signal注册安装一个信号
    if (signal(SIGINT, handle) == SIG_ERR)
        ERR_EXIT("signal error");
    for(;;);
    return 0;
}

void handle(int sig)
{
    printf("recv a sig=%d\n", sig);
}
