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
    
//将0和标准输入断开，重新指向了Makefile文件
//也就是，标准输入指向了Makefile
    close(0);
    open("Makefile", O_RDONLY);

    //同理。1指向了Makefile2
    close(1);
    open("Makefile2", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    
//不带参数的cat表示：从标准输入获取命令，写入到标准输出
//从Makefile获取数据，写入到Makefile2中
    execlp("cat", "cat", NULL);

    return 0;
}





