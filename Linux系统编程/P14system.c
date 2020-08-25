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

int my_system(const char *command);
int main(int argc, char *argv[])
{
    system("ls -l|wc -l");
    //my_system("ls -l|wc -l");
    return 0;
}



//实现一个system函数，了解system的机制
int my_system(const char *command)
{
    pid_t pid;
    int status;
    if (command == NULL)
        return 1;
    
    if ((pid = fork()) <0)
        status = -1;
    else if (pid == 0)
    {
        //通过man execl查询，...可知
        // int execl(const char *path, const char *arg, ...
        //             /* (char  *) NULL */);

        //execl尾巴要有一个空指针NULL,表示参数结束
        execl("/bin/sh", "sh", "-c", command, NULL);
        exit(127);//出错返回127
    }
    else
    {
        while (waitpid(pid, &status, 0) <0)
        {
            //被信号打断，重新去等待
            if (errno == EINTR)
                continue;
            status = -1;
            break;
        }
        
    }
    return status;


}




