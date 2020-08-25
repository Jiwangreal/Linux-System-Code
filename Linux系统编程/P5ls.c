#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#include <dirent.h>

#define ERR_EXIT(m) \
    do \
    { \
        perror(m);  \
        exit(EXIT_FAILURE); \
    } while(0)


//编写简单的ls命令
int main(void)
{
    DIR *dir = opendir(".");//打开当前目录
    struct dirent *de;
    while ((de = readdir(dir)) != NULL)//man readdir
    {
        if (strncmp(de->d_name，"."， 1) == 0)
            continue;
        printf("%s\n", de->d_name);
    }
    
    close(dir);
    exit(EXIT_SUCCESS);//等价于exit(0);
}



