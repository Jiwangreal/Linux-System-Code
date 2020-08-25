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

    //替换之前的pid与hello程序输出的pid是一样的，替换之前与替换之后的pid应该是一样的
    printf("pid = %d\n", getpid());
    //将当前进程替换掉，代码段和数据段被替换了，但是进程控制块还是一样的，
    //所以只要替换成功，“Exiting main...\n”是不会输出的
    execlp("./hello", "hello", NULL);

    int ret = execlp("hello", "hello", NULL);
    if (ret == -1)
        perror("execlp error");
    printf("Exiting main...\n");
    return 0;
}

