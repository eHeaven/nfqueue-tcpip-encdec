#include "tcpip.h"


#ifdef __LITTLE_ENDIAN 
#define IPQUAD(addr)            \
                ((unsigned char *)&addr)[0],     \
                ((unsigned char *)&addr)[1],     \
                ((unsigned char *)&addr)[2],     \
                ((unsigned char *)&addr)[3] 
#else 
#define IPQUAD(addr)            \
                ((unsigned char *)&addr)[3],     \
                ((unsigned char *)&addr)[2],     \
                ((unsigned char *)&addr)[1],     \
                ((unsigned char *)&addr)[0] 
#endif

static u_int16_t checksum(u_int32_t init, u_int8_t *addr, size_t count)
{
    /* Compute Internet Checksum for "count" bytes * beginning at location "addr". */ 
    u_int32_t sum = init; 
    while( count > 1 )
    { 
        /* This is the inner loop */ 
        sum += ntohs(* (u_int16_t*) addr);     
        addr += 2;     
        count -= 2;    
    }
    /* Add left-over byte, if any */ 
    if( count > 0 ) sum += ntohs(( *(u_int8_t *) addr ));
    /* Fold 32-bit sum to 16 bits */ 
    while (sum>>16) sum = (sum & 0xffff) + (sum >> 16); 

    return (u_int16_t)~sum;
} 
void set_ip_checksum(struct iphdr* iphdrp)
{   
    iphdrp->check = 0;    
    iphdrp->check = htons(checksum(0, (u_int8_t*)iphdrp, iphdrp->ihl<<2));  
} 
static u_int16_t tcp_checksum2(struct iphdr* iphdrp, struct tcphdr* tcphdrp)
{ 
    size_t tcplen = ntohs(iphdrp->tot_len) - (iphdrp->ihl<<2); 
    u_int32_t cksum = 0;     
    cksum += ntohs((iphdrp->saddr >> 16) & 0x0000ffff);   
    cksum += ntohs(iphdrp->saddr & 0x0000ffff);   
    cksum += ntohs((iphdrp->daddr >> 16) & 0x0000ffff);
    cksum += ntohs(iphdrp->daddr & 0x0000ffff);
    cksum += iphdrp->protocol & 0x00ff;
    cksum += tcplen; 
    return checksum(cksum, (u_int8_t*)tcphdrp, tcplen);
} 

static void set_tcp_checksum2(struct iphdr* iphdrp, struct tcphdr* tcphdrp)
{
    tcphdrp->check = 0;
    tcphdrp->check = htons(tcp_checksum2(iphdrp, tcphdrp));
}

void set_tcp_checksum1(struct iphdr* iphdrp)
{ 
    struct tcphdr *tcphdrp = (struct tcphdr*)((u_int8_t*)iphdrp + (iphdrp->ihl<<2)); 
    set_tcp_checksum2(iphdrp, tcphdrp);
} 

static u_int16_t udp_checksum2(struct iphdr* iphdrp, struct udphdr* udphdrp)
{ 
    size_t udplen = ntohs(iphdrp->tot_len) - (iphdrp->ihl<<2); 
    u_int32_t cksum = 0;     
    cksum += ntohs((iphdrp->saddr >> 16) & 0x0000ffff);   
    cksum += ntohs(iphdrp->saddr & 0x0000ffff);   
    cksum += ntohs((iphdrp->daddr >> 16) & 0x0000ffff);
    cksum += ntohs(iphdrp->daddr & 0x0000ffff);
    cksum += iphdrp->protocol & 0x00ff;
    cksum += udplen; 
    return checksum(cksum, (u_int8_t*)udphdrp, udplen);
} 
static void set_udp_checksum2(struct iphdr* iphdrp, struct udphdr* udphdrp)
{
    udphdrp->check = 0;
    udphdrp->check = htons(udp_checksum2(iphdrp, udphdrp));
}

void set_udp_checksum1(struct iphdr* iphdrp)
{ 
    struct udphdr *udphdrp = (struct udphdr*)((u_int8_t*)iphdrp + (iphdrp->ihl<<2));
    set_udp_checksum2(iphdrp, (struct udphdr*)udphdrp);
}