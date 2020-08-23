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

int gval = 100;
int main(int argc, char *argv[])
{
    signal(SIGCHLD, SIG_IGN);
    printf("before fork pid = %d\n", getpid());
    int fd;
    
    pid_t pid;
    pid = vfork();
    if (pid == -1)
        ERR_EXIT("fork error");
    if (pid > 0)
    {
        sleep(1);//目的是让子进程先进行gval++操作
        printf("this is parent pid=%d child pid =%d gval=%d\n", getpid(), pid, gval);
        sleep(3);
    }
    else if (pid = 0)
    {
        gval++;
        printf("this is child pid =%d parent pid =%d\n gval=%d\n", getpid(), getppid(), gval);
        _exit(0);//与exit(0)结果一样
    }

    return 0;
}




