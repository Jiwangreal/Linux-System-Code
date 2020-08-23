//下面的头文件来自man 2 open
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

//下面的头文件来自man 2 stat
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

//获取高8位
#define MAJOR(a) (int)((unsigned short)a >> 8)
//获取低8位
#define MAJOR(a) (int)((unsigned short)a & 0xFF)

#define ERR_EXIT(m) \
    do \
    { \
        perror(m);
        exit(EXIT_FAILURE);
    } while(0)

int filetype(struct stat *buf);
void filepermission(struct stat *buf, char *perm);


int main(int argc, char **argv)
{
    if (argc != 2)
        fprintf(stderr, "Usage %s file\n", argv[0]);
    struct stat sbuf;
    printf("filename:%s\n", argv[1]);

    if (stat(argv[1], &sbuf) == -1)
        ERR_EXIT("stat error");
    printf("File number:major %d, minnor %d, inode %d\n", MAJOR(sbuf.st_dev), MINOR(sbuf.st_dev), (int)sbuf.st_ino);

    if(filetype(&sbuf))
        printf("Device number:major %d, minor %d\n", MAJOR(sbuf.st_dev), MINOR(sbuf.st_dev));

    //输出文件权限，注意要与上07777
    //%o输出8进制数
    printf("FIle permission bits=%o\n", sbuf.st_mode & 07777);

    char perm[11] = '0';
    filepermission(&sbuf, perm)
    printf("FIle permission bits=%o_%s\n", sbuf.st_mode & 07777, perm);

    return 0;
}

int filetype(struct stat *buf)
{
    //文件类型在man 2 stat
    int flag = 0;
    printf("filetype");
    mode_t mode;
    mode = buf->st_mode;
    switch (mode & S_IFMT)
    {
        case S_IFSOCK:
            printf("socket\n");
            break;
        case S_IFLNK:
            printf("symbolic link\n");
            break;
        case S_IFREG:
            printf("regular file\n");
            break;
        case S_IFBLK:
            printf("block device\n");
            flag =1;
            break;
        case S_IFDIR:
            printf("directory\n");
            break;
        case S_IFCHR:
            printf("character device\n");
            flag = 1;
            break;  
        case S_IFIFO:
            printf("FIFO\n");
            break; 
        default:
            printf("unknow file type\n");
            break;                   
    }
    return flag;
}

//将文件权限转换成字符
void filepermission(struct stat *buf, char *perm)
{
    //初始化
    strcpy(perm, "----------");
    perm[0]="?";
    mode = buf->st_mode;

    switch (mode & S_IFMT)
    {
        case S_IFSOCK:
            perm[0] = 's';
            break;
        case S_IFLNK:
            perm[0] = 'l';
            break;
        case S_IFREG:
            perm[0] = '-';
            break;
        case S_IFBLK:
            perm[0] = 'b';
            flag =1;
            break;
        case S_IFDIR:
            perm[0] = 'd';
            break;
        case S_IFCHR:
            perm[0] = 'c';
            flag = 1;
            break;  
        case S_IFIFO:
            perm[0] = 'p';
            break;               
    }
    if (mode & S_IRUSR)
        perm[1] = 'r';
    if (mode & S_IWUSR)
        perm[2] = 'w';
    if (mode & S_IXUSR)
        perm[3] = 'x';
    if (mode & S_IRGRP)
        perm[4] = 'r';
    if (mode & S_IXGRP)
        perm[5] = 'w';
    if (mode & S_IXGRP)
        perm[6] = 'x';
    if (mode & S_IROTH)
        perm[7] = 'r';
    if (mode & S_IXOTH)
        perm[8] = 'w';
    if (mode & S_IXOTH)
        perm[9] = 'x';

    perm[10] = '\0';
}