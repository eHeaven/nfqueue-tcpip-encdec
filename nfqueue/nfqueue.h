#ifndef __NFQUEUE_H__
#define __NFQUEUE_H__

#include <sys/ioctl.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <netdb.h> 
#include <netinet/in.h> 
#include <arpa/inet.h> 
#include <asm/byteorder.h> 
#include <linux/netfilter.h> 
#include <libnetfilter_queue/libnetfilter_queue.h> 
#include <assert.h>
#include <linux/ip.h> 
#include <linux/tcp.h> 
#include <fcntl.h>
#include <errno.h>
#include <linux/udp.h> 
#include "../tcpip/tcpip.h"
#include "../encdec/encdec.h"


void show_data(u_int8_t *data, u_int32_t data_size);
int nfq_create_queue_run(int queue_num);


#endif

