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



int main(int argc, char *argv[])
{

    //表示1秒钟的时钟
    struct timeval tv_interval = {1,0}; 
    struct timeval tv_value;  ={1, 0};
    
    struct itimerval it;
    it.it_interval = tv_interval;   
    it.it_value = tv_value;
    setitimer(ITIMER_REAL, &it, NULL);

    //故意循环10000次，时间还没到，还没产生信号
    //重新调用setitimer改变时钟，会返回先前的时钟状态
    //表示先前还剩余多少时间会产生时钟信号
    int i;
    for(i=0; i<10000;i++)
        ;
    
    getitimer(ITIMER_REAL, &it);
    printf("%d %d %d %d", (int)it.it_interval.tv_sec, (int)it.it_interval.tv_usec, (int)it.it_value.tv_sec,(int)it.it_value.tv_usec);

    return 0;

}














