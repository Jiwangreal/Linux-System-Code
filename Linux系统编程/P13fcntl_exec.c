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
    printf("Entering main ...\n");
    //将标准输出fd的FD_CLOSEEXC进行置位，说明1号文件描述符已经被关闭了
    //hello2程序是无法输出的
    //与man 2 open的flags的O_CLOEXEC的功能是一样的
    int ret = fcntl(1, F_SETFD, FD_CLOEXEC);
    if (ret == -1)
        ERR_EXIT("fcntl error");

    execlp("./test1", "tes1", NULL);

    printf("Exiting main...\n");
    return 0;
}





