#include <unistd.h>
#include <error.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    int ret;
    ret = close(10);//关闭文件描述符10
    //错误输出方式1
    // if (ret == -1)
    //     perror("close error");//perror将全局变量errno转换成了错误的文本信息，并且直接输出到了标准错误设备stderr
    
    //错误输出方式2
    //strerror将错误码转换成文本方式输出，错误码已经保存在全局变量errno中了
    // if (ret == -1)
    //     fprintf(stderr, "close srror with msg : %s\n", strerror(errno));

    printf("EINTR desc = %s\n", strerror(EINTR));
    return 0;
}