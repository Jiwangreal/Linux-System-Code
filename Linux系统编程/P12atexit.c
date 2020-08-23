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

//\n会将缓冲区清除，输出到标准输出设备
void my_exit1(void)
{
    printf("my exit1 ...\n");
} 


void my_exit2(void)
{
    printf("my exit2 ...\n");
} 

int main(int argc, char *argv[])
{
    //注册了2个终止处理程序
    atexit(my_exit1);//先安装my_exit1，后安装my_exit2
    atexit(my_exit2);
    exit(0);//若改为_exit(0)，则不会有任何输出，_exit是不会调用终止处理程序的，
    //因为终止处理程序也是C库来安装的，内核并不知道安装了这些信息
}



