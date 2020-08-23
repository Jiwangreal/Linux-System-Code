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
    int outfd；
    outfd = open("Makefile2", O_WDONLY | O_CREAT | O_TRUNC， 0644);
    if (outfd == -1)
        ERR_EXIT("open");

    int infd;
    infd = open("tp", O_RDONLY);
    if (infd == -1)
        ERR_EXIT("open");
    char buf[1024];
    int n;
    while((n = read(infd, buf, 1024)) > 0)
    {
        write(outfd, buf, n);
    }
    close(infd);
    close(outfd);

    //man unlink,可以删除文件连接，当文件连接数为0的时候，文件将被删除
    unlink("tp");
    return 0;
}