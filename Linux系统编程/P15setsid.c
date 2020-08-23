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



//调用者进程将称为新会话期的领头进程
//调用者进程成为新会话期中唯一的一个进程组的组长
//新的会话期没有控制终端
//调用者进程的进程号是进程组的号，也是会话期的号码
int setup_daemon(void);

//模拟daemon函数
int setup_daemon(int nochdir，int noclose);
int main(void)
{
    setup_daemon();
    //daemon函数功能等于setup_daemon
    //daemon(0,0);//daemon(1,1);表示不更改根目录，不对标准输入、正确输出、错误输出进行重定向
    printf("test...\n");
    for(;;);
    return 0;
}

int setup_daemon(void)
{
    pid_t pid;
    pid = fork();
    if (pid == -1)
        ERR_EXIT("fork error");

    if (pid > 0)
        ERR_EXIT("EXIT_SUCCESS");
    setsid();
    chdir("/");//更改守护进程的当前目录为/目录，因为守护进程是长期运行在
                //后台的，当前目录不应该成为其运行环境目录
    //将标准输入、标准输出、标准错误重定向到/dev/null
    int i;
    for (i = 0;i<3; ++i)
        close(i);
    open("/dev/null", O_RDWR);//返回值为0，标准输入设备重定向到/dev/null
    dup(0);//标准输出也指向/dev/null
    dup(0);//标准错误输出也指向/dev/null
    return 0;
}

int setup_daemon(int nochdir，int noclose)
{
    pid_t pid;
    pid = fork();
    if (pid == -1)
        ERR_EXIT("fork error");

    if (pid > 0)
        ERR_EXIT("EXIT_SUCCESS");
    
    setsid();
    if (nochdir == 0)
        chdir("/");//更改守护进程的当前目录为/目录，因为守护进程是长期运行在
                //后台的，当前目录不应该成为其运行环境目录
    //将标准输入、标准输出、标准错误重定向到/dev/null
    if (noclose == 0)
    {
        int i;
        for (i = 0;i<3; ++i)
            close(i);
        open("/dev/null", O_RDWR);//返回值为0，标准输入设备重定向到/dev/null
        dup(0);//找一个空闲的文件描述符，空闲的fd是1，那么标准输出也指向/dev/null
        dup(0);//再找一个空闲的文件描述符，空闲的fd是2，标准错误输出也指向/dev/null
    }

    return 0;
}