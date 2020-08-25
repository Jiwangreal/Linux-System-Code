
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

//测试管道的容量
int main(int argc, char *argv[])
{
    int pipefd[2];
    if (pipe(pipefd) == -1)
        ERR_EXIT("pipe error");

    int ret;
    int count = 0;
    while (1)
    {
        //管道模式是阻塞的
        ret = write(pipefd[1], "A", 1);
        if (ret == -1)
            break;
        count++;
    }
    return 0;
}