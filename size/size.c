#include <stdio.h>
#include <sys/ioctl.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <netdb.h> 
#include <netinet/in.h> 
#include <arpa/inet.h> 
#include <string.h>
//定义winsize 结构体变量， 获取当前终端的大小
struct winsize size;

int main(int argc, const char **argv)
{
    int i, num = 0;
    // 获取到终端的大小数据
    ioctl(STDIN_FILENO,TIOCGWINSZ,&size);
    // 打印出和终端大小一样的框框
    
    // printf("%s\n", argv[1]);
    if(memcmp( argv[1], "1", 1) == 0 )
    {
        for(i = 0; i < size.ws_col; i++) printf("*");
    }
    else if(memcmp( argv[1], "2", 1) == 0 ) 
    {
        printf("* ");
        if(argc > 2)
        {
            printf("    ");
            for(i = 2; i < argc; i++) num += strlen(argv[i]);
            for(i = 2; i < argc; i++) printf("%s\n", argv[i]);
            for(i = 0; i < size.ws_col - 5 - argc  - num; i++) printf(" ");
        }
        else
        {
            for(i = 0; i < size.ws_col - 3; i++) printf(" ");
        }
        printf("*");
    }
    else if(memcmp( argv[1], "3", 1) == 0 )
    {
        printf("*");
        for(i = 2; i < argc; i++) num += strlen(argv[i]);
        int abcbdbd = (size.ws_col - num - argc) / 2;
        for(i = 0; i < abcbdbd; i++) printf(" ");
        for(i = 2; i < argc; i++) printf("%s\n", argv[i]);
        if((size.ws_col - num - argc) % 2 != 0 )  abcbdbd += 1;
        for(i = 0; i < abcbdbd; i++) printf(" "); 
        printf("*");
    }
    else 
    {
        printf("* ");
        for(i = 1; i < argc; i++) printf("%s\n", argv[i]);
        for(i = 1; i < argc; i++) num += strlen(argv[i]);
        for(i = 0; i < size.ws_col - num - 2 - argc; i++) printf(" ");
        printf("*");
    }
    return size.ws_col;
}