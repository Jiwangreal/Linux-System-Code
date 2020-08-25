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
    char *const envp[] ={"AA=11", "BB=22", NULL}

    //指定envp环境变量项，传递给hello2进程
    int ret = execle("./test2", "hello", NULL, envp);
    // int ret = execl("./test2", "hello", NULL);
    if (ret == -1)
        ERR_EXIT("execl error");
    printf("Exiting main...\n");
    return 0;
}

