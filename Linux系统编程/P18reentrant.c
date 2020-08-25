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

typedef struct 
{
    int a;
    int b;
}TEST;

TEST g_data;

void handle(int sig);
int main(int argc, char *argv[])
{
    TEST zeros = {0, 0};
    TEST ones = {1, 1};
    if (signal(SIGALRM, handle) == SIG_ERR)
        ERR_EXIT("signal error");
    
    g_data = zeros;
    for(;;)
    {
        g_data = zeros;
        g_data = ones;
    }
        
    return 0;
}

void unsafe_fun()
{
    printf("%d_%d\n", g_data.a, g_data.b);//printf本身就是不可重入函数
    //因为printf访问了全局变量，有可能导致不可重入函数
    //若printf没有访问全局变量，则还算是一个可重入函数
}

void handle(int sig)
{
    unsafe_fun();
    alarm(1);
}
