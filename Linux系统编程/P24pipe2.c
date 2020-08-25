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
    int pipefd[2];
    if (pipe(pipefd) == -1)
        ERR_EXIT("pipe error");

    pid_t pid;
    pid = fork();
    if (pid == -1)
        ERR_EXIT("fork error");

    if (pid == 0)
    {
        //关闭子进程的写端
        close(pipefd[1]);
        ERR_EXIT(EXIT_SUCCESS);
    }
    //关闭父进程的写端
    close(pipefd[1]);
    sleep(1);
    char buf[10] = {0};
    int ret = read(pipefd[0]. buf, 10);
    printf("ret = %d \n", ret);

    return 0;
}