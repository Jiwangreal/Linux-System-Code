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

int main(int argc, char *argv[])
{
    //fork一次，返回2个
    //fork之前进程数是1个，fork之后进程数是2个，也就
    //是说有2个进程要执行第2个fork，1进程——>2进程——>4进程——>8个进程
    fork();
    fork();
    fork();
    printf("ok\n");
}