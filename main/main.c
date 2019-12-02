#include "../encdec/encdec.h"
#include "../nfqueue/nfqueue.h"
#include "../tcpip/tcpip.h"

#include <stdio.h>
// #define ENCLENBASE 16
// extern unsigned char keyDataUnion[16][16];
// extern unsigned char ivData[16];
// unsigned char randomNum = 0;

/* 将数据写进文件 */
int msg2file(unsigned char *src, int len, const char *filename)
{
    int i = 0;
    char buf[1024 * 5] = {0}, *p = buf;
    // echo 1234
    sprintf(buf, "echo ");
    for (i = 0; i < len; i++)
        sprintf(p + 5 + i * 2, "%02X", src[i]);
    sprintf(p + 5 + i * 2, " >> %s", filename);
    system(buf);
    p = NULL;
    return 0;
}

int main(int argc, const char **argv)
{
    if (argc < 2)
    {
        printf("Usage : ./main queue-num\n");
        exit(-1);
    }

    if (atoi(argv[1]) <= 0 || atoi(argv[1]) > 65535)
    {
        printf("queue-num should not be 0, error!\n");
        exit(-1);
    }

    nfq_create_queue_run(atoi(argv[1]));

    return 0;
}