//下面的头文件来自man 2 open
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

// #define ERR_EXIT(m) (perror(m), exit(EXIT_FAILURE))
//等价于下面的一条一句，注意斜杠后面不能有空格,前面可以有空格
#define ERR_EXIT(m) \
    do \
    { \
        perror(m);  \
        exit(EXIT_FAILURE); \
    } while(0)


int main(void)
{
    int fd;
    //O_RDONLY只读方式打开
    fd = open("test.txt", O_RDONLY);
    if (fd == -1)
    {
        fprintf(stderr,"open error with errno=%d_%s\n", errno, strerror(errno));//错误输出方法1
        perror("open error");//错误输出方法2
        ERR_EXIT("open error");//错误输出方法3
        exit(EXIT_FAILURE); \//EXIT_FAILURE=1
    }

    printf("open succ\n");
    return 0;
}