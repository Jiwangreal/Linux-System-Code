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

//PIPE_BUF是4KB，用大于>4K 就行了，但是不容易测出穿插情况
//所以用了68K
//68KB
#define TEST_SIZE 68*1024

int main(int argc, char *argv[])
{
    char a[TEST_SIZE];
    char b[TEST_SIZE];

    memset(a, 'a', sizeof(a));
    memset(b, 'b', sizeof(b));

    int pipefd[2];

    int ret  = pipe(pipefd);
    if (ret == -1)
        ERR_EXIT("pipe error");

    pid_t pid;
    pid = fork();
    //子进程a
    if (pid == 0)
    {
        close(pipefd[0]);
        ret = write(pipefd[1], a, sizeof(a));//往管道写入68K的数据
        printf("apid = %d write %d bytes to pipe\n", getpid(), ret);
        exit(0);
    }
    pid = fork();
    //子进程b
    if (pid == 0)
    {
        close(pipefd[0]);
        ret = write(pipefd[1], b, sizeof(a));//往管道写入68K的数据
        printf("bpid = %d write %d bytes to pipe\n", getpid(), ret);
        exit(0);
    }

    //初始的父进程，接收进程a和进程b的数据
    close(pipefd[1]);
    sleep(1);
    int fd = open("test.txt", O_WRPNLY | O_CREAT| O_TRUNC, 0644);
    char buf[1024*4] = {0};
    int n = 1;
    while(1)
    {
        ret = read(pipefd[0], buf, sizeof(buf));
        //当连个子进程写端没数据了，就会返回=0
        if (ret == 0)
            break;
        //打印输出最后一个字符：buf[4095]
        printf("n=%2d pid =%d read %d bytes from pipe buf[4095]=%c\n", n++, getpid(), ret, buf[4095]);
        write(fd, buf, ret);
    }

    return 0;
}