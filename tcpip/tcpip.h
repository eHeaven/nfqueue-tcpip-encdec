#ifndef __TCPIP_H__
#define __TCPIP_H__

#include <sys/ioctl.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <netdb.h> 
#include <netinet/in.h> 
#include <arpa/inet.h> 
#include <asm/byteorder.h> 
#include <linux/ip.h> 
#include <linux/tcp.h> 
#include <linux/udp.h> 
#include <linux/hdreg.h>
#include <scsi/scsi.h>
#include <scsi/sg.h>
#include <linux/param.h>
#include <linux/fs.h>
#include <fcntl.h>
#include <errno.h>


void set_ip_checksum(struct iphdr* iphdrp);
void set_tcp_checksum1(struct iphdr* iphdrp);
void set_udp_checksum1(struct iphdr* iphdr);




#endif
