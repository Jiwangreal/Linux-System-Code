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

int main(int argc, char *argv[])
{
    printf("hello world");//区别：printf("hello world\n")；中的\n会将缓冲区清除，输出到标准输出设备
    //_exit+fflush才等价于exit(0)
    // fflush(stdout)；//若使用_exit(0);再使用fflush可以及时清除流，数据就输出到标准输出设备，延迟到
    //程序结束之后进行缓冲区的清除
    _exit(0);
    // return 0;//与exit(0)基本等价
}