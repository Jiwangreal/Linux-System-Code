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
        perror(m);  \
        exit(EXIT_FAILURE); \
    } while(0)

int main(int argc, char *argv[])
{
    // signal(SIGCHLD, SIG_IGN);//可以避免僵尸进程，当子进程退出时，会向父进程发送SIGCHLD信号
    printf("before fork pid = %d\n", getpid());
    
    pid_t pid;
    pid = fork();
    if (pid == -1)
        ERR_EXIT("fork error");
    if (pid > 0)
    {
        printf("this is parent pid=%d child pid =%d gval=%d\n", getpid(), pid);
        sleep(100);
    }
    else if (pid = 0)
    {
        printf("this is child pid =%d parent pid =%d gval=%d\n", getpid(), getppid());
    }

    return 0;
}
