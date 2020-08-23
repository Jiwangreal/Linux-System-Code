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

int main(int argc, char *argv[])
{
    printf("Entering main ...\n");
    
    // execlp("ls", "ls", "-l", NULL);
    //与execlp相比，execl的参数与其一样，但是ls命令必须指定全路径，他不会在全路径$PATH
    //下进行搜索,全路径可以是绝对的，也可以是相对的
    //带p，会到环境变量下找ls程序，不带p，则不会到环境变量下找ls程序
    int ret = execl("/bin/ls", "ls", "-l", NULL);
    if (ret == -1)
        ERR_EXIT("execl error");
    printf("Exiting main...\n");
    return 0;
}

