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


int main(int argc, int argv*[])
{
    //要对文件加读锁，那么要对文件有读的权限
    //要对文件加写锁，那么要对文件有写的权限    
    int fd;
    fd = open("test2.txt", O_CREAT | O_RDWR | O_TRUNC, 0644);
    if (fd == -1)
        ERR_EXIT("open error");
    struct flock lock;
    memset(&lock, 0, sizeof(lock));
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;//基准位置
    lock.l_start = 0;//偏移位置
    lock.len = 0;//为0表示锁定整个文件

    if (fcntl(fd, F_SETLK, &lock) == 0)
    {
        printf("lock success\n");
        printf("press any key to unloc\nk");
        getchar();//按下任意键
        lock.l_type = F_UNLOCK;
        if (fcntl(fd, F_SETLK, &lock) == 0)
            printf("unlock success\n");
        else
            printf("unlock fail\n");
        
    }
    else
    {
        ERR_EXIT("lock fail\n");
    }

    //就算没解锁，当进程退出的时候也会释放锁
    return 0;
    
}






