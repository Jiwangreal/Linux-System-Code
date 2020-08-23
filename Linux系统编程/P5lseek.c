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

int main(void)
{
    int fd;
    fd = open("test.txt", O_RDONLY);
    if (fd == -1)
        ERR_EXIT("open error");
    char buf[1024] = {0};
    int ret = read(fd, buf ,5);//读取5个字节到缓冲区，文件指针在5的位置
    if (ret == -1)
        ERR_EXIT("read error");

    printf("buf = %s\n", buf);
    
    //从当前指针所在位置偏移，偏移0个字节，返回值就是偏移量
    //该偏移量就等于当前指针所在的位置
    ret =lseek(fd, 0, SEEK_CUR);
    if (ret == -1)
        ERR_EXIT("lseek");
    printf("current offset = %d\n", ret);

    return 0;
}







