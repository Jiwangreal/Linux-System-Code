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

void set_flag(int fd, int flags);
void clr_flag(int fd, int flags);
int main(int argc, char *argv[])
{
    char buf[1024] = {0};
    int ret;

    int flags;
    //先获取fd的状态
    flags = fcntl(0, F_GETFL, 0);
    if (flags == -1)
        ERR_EXIT("fcntl get flag error");
    
    //再设置fd的状态，因为若直接获取，会移除以前fd的其它状态
    ret = fcntl(0, FSETTFL, flags | O_NONBLOCK);
    if (flags == -1)
        ERR_EXIT("fcntl set flag error");

    //set_flag(fd, O_ONOBLOCK);
    //clr_flag(fd, O_ONOBLOCK);
    ret =read(0, buf, 1024);
    if (ret == -1)
        ERR_EXIT("read error");
    
    printf("buf=%s\n", buf);

    return 0;
}

void set_flag(int fd, int flags)
{
    //先获取fd的状态
    int val;
    val = fcntl(fd, F_GETFL, 0);
    if (val == -1)
        ERR_EXIT("fcntl get flag error");
    
    val | =flags;
    //再设置fd的状态，因为若直接获取，会移除以前fd的其它状态
    ret = fcntl(fd, FSETTFL, val);
    if (flags == -1)
        ERR_EXIT("fcntl set flag error");
}

//清除fd的状态
void clr_flag(int fd, int flags)
{
    //先获取fd的状态
    int val;
    val = fcntl(fd, F_GETFL, 0);
    if (val == -1)
        ERR_EXIT("fcntl get flag error");
    
    val & = ~flags;
    //再设置fd的状态，因为若直接获取，会移除以前fd的其它状态
    ret = fcntl(fd, FSETTFL, val);
    if (flags == -1)
        ERR_EXIT("fcntl set flag error");
}