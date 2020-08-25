#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>


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
    pid_t pid;
    pid=fork();
    if (pid == -1)
    {
        ERR_EXIT("fork error");
    }

    if (pid == 0)
    {
        sleep(3);
        printf("this is child");
        // exit(100);//子进程已经退了
        abort();//abort函数可以模拟异常终止
    }
    printf("this is parent\n");
    int status;
    int ret;
    //就算父进程先运行到这里，但是父进程会阻塞在wait，一定要先等待子进程先退出
    //wait函数会挂起，直到子进程退出
    //子进程退出时，会将进程置为僵尸状态，而父进程会查询该状态，子进程就不会出现僵尸
    ret = wait(&status);//父进程wait等待子进程的退出，保证子进程先退出，父进程后退出
    printf("ret = %d pid = %d\n", ret, pid);
    if  (WIFEXITED(status))
        printf("child exited normal exit status=%d\n", WEXITSTATUS(status));
    else if (WIDDIGNALED(status))
        printf("child exited abnormal signal number=%d\n", WTERMSIG(status));//WTERMSIG获取哪个信号
    else if (WIFSTOPPED)
          printf("child stopped signal number=%d\n", WSTOPSIG(status));
 
    
    return 0;
}


