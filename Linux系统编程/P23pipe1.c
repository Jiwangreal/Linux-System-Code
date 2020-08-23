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
    int pipefd[2];
    if (pipe(pipefd) == -1)
        ERR_EXIT("pipe error");

    pid_t pid;
    pid = fork();
    if (pid == -1)
        ERR_EXIT("fork error");

    if (pid == 0)
    {
        //复制管道的写端，意味着1指向管道的写端
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);//因为1（标准输入）已经指向了管道的写端，所以可以close(pipefd[1])
        close(pipefd[0]);//读端没啥用了，关闭即可
        execlp("ls", "ls", NULL);
        fprintf(stderr, "error execute ls\n");
        ERR_EXIT(EXIT_SUCCESS);
    }
    //复制管道的都端，意味着0指向管道的读端
    //0是标准输出
    dup2(pipefd[0], STDIN_FILENO);
    close(pipefd[0]);
    close(pipefd[1]);
    execlp("ls", "wc", "-w", NULL);
    fprintf(stderr, "error execute ls\n");
    ERR_EXIT(EXIT_SUCCESS);


    return 0;
}