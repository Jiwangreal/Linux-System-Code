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
        perror(m);  \
        exit(EXIT_FAILURE); \
    } while(0)

int main(int argc, char *argv[])
{
    int fd1;

    fd = open("test2.txt", O_RDONLY);
    if (fd1 == -1)
        ERR_EXIT("open error");
    
    //返回一个新的文件描述符，与fd指向同一个文件
    //当前新的文件描述符是1，因为将fd=1关闭了
    close(1);//将fd=1关闭了，所以返回的文件描述符的值为1，所以1和fd指向同一个文件
    dup(fd);
    //上面的2行，等价于dup2(fd,1);

    //当前的标准输出不再指向屏幕，而是指向了text2
    printf("hello\n");
    return 0;
}