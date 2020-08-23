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
    _sighandler_t oldhandler;
    oldhandler = signal(SIGINT, handler);
    if (oldhandler == SIG_ERR)
        ERR_EXIT("signal error");
    
    while (getchar() != '\n')//循环接收一个字符
        ;
    
    //按下空格后，重新关联成了默认的处理程序
    //等价于信号的默认操作，signal(SIGINT, SIG_FFL)，将其重新关联成信号的默认操作
    if (signal(SIGINT, oldhandler) == SIG_ERR)
        ERR_EXIT("signal error");
    for(;;);
    return 0;
}

void handler(int sig)
{
    printf("recv a sig=%d\n", sig);
}
