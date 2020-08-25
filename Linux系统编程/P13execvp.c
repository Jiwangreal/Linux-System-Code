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
    printf("Entering main ...\n");
    
    char *const args[] = {"ls", "-l", NULL};
    //将当前进程替换掉，代码段和数据段被替换了，但是进程控制块还是一样的，
    //所以只要替换成功，“Exiting main...\n”是不会输出的
    //execlp(程序文件名称，参数表(第一个参数是ls，第二个参数是-l)，参数结束是NULL控制在);
    // execlp("ls", "ls", "-l", NULL);
    //与execlp相比较，execvp将可变参数列表保存到变量argv中
    execvp("ls", args);
    printf("Exiting main...\n");
    return 0;
}

