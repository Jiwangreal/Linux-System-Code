//下面的头文件来自man 2 open
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#define ERR_EXIT(m) \
    do \
    { \
        perror(m);  \
        exit(EXIT_FAILURE); \
    } while(0)


int main(void)
{
    umask(0);
    int fd;
    fd = open("test.txt", O_WRDONLY| O_CREAT, 0666);
    if (fd == -1)
    {

        ERR_EXIT("open error");
        exit(EXIT_FAILURE); \
    }

    printf("open succ\n");
    return 0;
}