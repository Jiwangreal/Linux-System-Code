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


//空洞文件的eg
int mian(void)
{
    int fd;
    fd = open("hole.txt", O_WRONLY| O_CREAT| O_TRUNC, 0644);
    if (fd == -1)
        ERR_EXIT("open with error");
    write(fd, "ABCDE", 5);
    int ret = lseek(fd, 32, SEEK_CUR);
    // int ret = lseek(fd, 1024*1024*1024, SEEK_CUR);//仅仅在内核操作，不会在磁盘IO进行操作
    if (ret == -1)
        ERR_EXIT("lseek error");
    write(fd, "hello", 5);
    close(fd);
    return 0;
}