#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <sys/time.h>


#define ERR_EXIT(m) \
    do \
    { \
        perror(m);
        exit(EXIT_FAILURE);
    } while(0)

void  handler(int sig)
{
    printf("recv a sig=%d\n", sig);
}

int main(int argc, char *argv[])
{
    if(signal(SIGALARM, handler) == SIG_ERR)
        ERR_EXIT("signal error");

    //表示1秒钟的时钟
    struct timeval tv_interval = {1,0}; 
    struct timeval tv_value;  ={1, 0};
    
    struct itimerval it;
    it.it_interval = tv_interval;//今后产生信号的间隔时间    
    it.it_value = tv_value;//第一次产生信号需要的时间（第一次吃药的时间较长，后面吃药时间就短了）
    //NULL表示不关心原来的值
    //setitimer间歇性的产生时钟
    setitimer(ITIMER_REAL, &it, NULL);

    for(;;)
        pause();
    return 0;

}














