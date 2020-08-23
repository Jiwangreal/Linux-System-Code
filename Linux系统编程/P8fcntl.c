#include <unistd.h>
#include <sys/stat.h>
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

int main(int argc, char *argv[])
{
    int fd1;

    fd = open("test.txt", O_RDONLY);
    if (fd1 == -1)
        ERR_EXIT("open error");

    // close(1);//将fd=1关闭了，所以返回的文件描述符的值为1，所以1和fd指向同一个文件
    // dup(fd);
    // //上面的2行，等价于dup2(fd,1);

    //fcntl模拟复制文件描述符
    close(1);//关闭标准输出，因为默认0，1，2已经被打开了

    //因为fcntl是从0搜索的，所以当前得到可以用的fd=1
    if (fcntl(fd, F_DUPFD, 0) <0)
        ERR_EXIT("fcntl with error");
    

    printf("hello\n");//输出到标准输出，标准输出已经重定位到test.txt
    return 0;
}