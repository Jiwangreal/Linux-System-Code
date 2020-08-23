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
        perror(m);
        exit(EXIT_FAILURE);
    } while(0)

//实现拷贝文件的功能
int main(int argc, char* argv[])
{
    int infd;
    int outfd;
    if (argc !=3 )
    {
        fprintf(stderr, "Usage %s src dts", argv[0]);
        ERR_EXIT(EXIT_FAILURE);
    }

    infd = open(argv[1], O_RDONLY);
    if (infd == -1)
        ERR_EXIT("open src error");
    if ((outfd = open(argv[2], O_WDONLY|O_CREAT|O_TRUNC, 0644)) == -1)
        ERR_EXIT("open dst error");

    //将infd的内容写入到outfd
    char buf[1024];
    int nread;
    while ((nread = read(infd, buf, 1024) >0)
    {
        write(outfd, buf, 1024);
    }
    close(infd);
    close(outfd);
    return 0;
}