#include "nfqueue.h"

//定义winsize 结构体变量， 获取当前终端的大小
struct winsize size;
#define ENCLENBASE 16
extern unsigned char keyDataUnion[16][16];
extern unsigned char ivData[16];

#ifdef __LITTLE_ENDIAN
#define IPQUAD(addr)                 \
    ((unsigned char *)&addr)[0],     \
        ((unsigned char *)&addr)[1], \
        ((unsigned char *)&addr)[2], \
        ((unsigned char *)&addr)[3]
#else
#define IPQUAD(addr)                 \
    ((unsigned char *)&addr)[3],     \
        ((unsigned char *)&addr)[2], \
        ((unsigned char *)&addr)[1], \
        ((unsigned char *)&addr)[0]
#endif

void show_data(u_int8_t *data, u_int32_t data_size)
{
    u_int32_t i = 0;
    for (i = 0; i < data_size; ++i)
        printf("%02X", data[i]);
    printf("\n");
}

// 回调函数定义, 基本结构是先处理包,然后返回裁定
static int cb(struct nfq_q_handle *qh, struct nfgenmsg *nfmsg, struct nfq_data *nfa, void *data)
{
    u_int32_t id = 0, i;
    struct nfqnl_msg_packet_hdr *ph;
    unsigned char *pdata = NULL;
    int pdataLen = 0, length = 0;
    u_int8_t *payload_offset = NULL;
    struct tcphdr *tcphdrp = NULL;
    struct udphdr *udphdrp = NULL;
    uint16_t sport = 0, dport = 0;
    struct nfqnl_msg_packet_hw *hwph = NULL;
    char src_mac[sizeof("ff:ff:ff:ff:ff:ff\0")];
    struct iphdr *iphdrp = NULL;

    unsigned char *outbuf = (unsigned char *)malloc(1024 * 5);

    // 提取数据包头信息,包括id,协议和hook点信息
    ph = nfq_get_msg_packet_hdr(nfa);
    if (ph)
        id = ntohl(ph->packet_id);
    // 获取数据包载荷,data指针指向载荷,从实际的IP头开始
    pdataLen = nfq_get_payload(nfa, ((unsigned char **)&pdata));
    if (pdataLen == -1)
        pdataLen = 0;
    iphdrp = (struct iphdr *)pdata;
    // 获取到终端的大小数据
    ioctl(STDIN_FILENO, TIOCGWINSZ, &size);
    // 打印出和终端大小一样的框框
    for (i = 0; i < size.ws_col; i++)
        printf("*");

    printf("packet: %u, protocol = %u, IPPROTO_TCP = %u\n", id, iphdrp->protocol, IPPROTO_TCP);

    if (iphdrp->protocol == IPPROTO_TCP)
    {
        tcphdrp = (struct tcphdr *)((u_int8_t *)iphdrp + (iphdrp->ihl << 2));
        length = pdataLen - (iphdrp->ihl << 2) - (tcphdrp->doff << 2);
        payload_offset = (u_int8_t *)((u_int8_t *)tcphdrp + (tcphdrp->doff << 2));
        sport = tcphdrp->source;
        dport = tcphdrp->dest;

        printf("line = %d, sport = %d, dport = %d, resl = %d\n", __LINE__, tcphdrp->source, tcphdrp->dest, tcphdrp->res1);

        int keyNum = ((length % ENCLENBASE) == 0 ? 1 : (length % ENCLENBASE));
        length -= length % ENCLENBASE;

        if (length >= ENCLENBASE) // 说明数据是加密的数据
        {
            // unsigned char key[20] = {0};
            // memcpy(key, keyDataUnion[tcphdrp->res1], 16);
            // hwph = nfq_get_packet_hw(nfa);
            // if(hwph) sprintf(src_mac, "%02x:%02x:%02x:%02x:%02x:%02x", hwph->hw_addr[0], hwph->hw_addr[1], hwph->hw_addr[2], hwph->hw_addr[3], hwph->hw_addr[4], hwph->hw_addr[5]);
            // printf("hw_addr : "); show_data(hwph->hw_addr, 6);
            // keyDataInit(keyDataUnion[tcphdrp->res1], hwph->hw_addr );
            printf("keyData : %d, %d\n", tcphdrp->res1, keyNum);
            show_data(keyDataUnion[keyNum], 16);
            printf("length = %d, payLoad : \n", length);
            show_data(payload_offset, length);
            Decrypt_cbc(payload_offset, outbuf, keyDataUnion[keyNum], ivData, length);
            memcpy(payload_offset, outbuf, length);
            printf("length = %d, payLoad : \n", length);
            show_data(payload_offset, length);
        }
    }
    set_ip_checksum(iphdrp);
    if (iphdrp->protocol == IPPROTO_TCP)
        set_tcp_checksum1(iphdrp);
    if (iphdrp->protocol == IPPROTO_UDP)
        set_udp_checksum1(iphdrp);

#if 0
    printf("pdataLen = %d, pdata : \n", pdataLen); show_data(pdata, pdataLen);
    if(length != 0)
    {
        u_int32_t mark, ifi;        
        struct nfqnl_msg_packet_hw *hwph;        
        printf("length = %d\n", length);
        printf("hw_protocol = 0x%04x, hook = %u, id = %u\n", ntohs(ph->hw_protocol), ph->hook, id);  
        
        hwph = nfq_get_packet_hw(nfa);
        if (hwph) 
        {
            int i, hlen = ntohs(hwph->hw_addrlen);
            printf("hw_src_addr = ");
            for (i = 0; i < hlen-1; i++) printf("%02X:", hwph->hw_addr[i]);
            printf("%02X \n", hwph->hw_addr[hlen-1]);
        }
        // 获取数据包的mark值, 也就是内核skb的nfmark值
        mark = nfq_get_nfmark(nfa);
        if (mark) printf("mark = %u \n", mark);
        // 获取数据包的进入网卡的索引号
        ifi = nfq_get_indev(nfa);
        if (ifi) printf("indev = %u \n", ifi);
        // 获取数据包的发出网卡的索引号
        ifi = nfq_get_outdev(nfa);
        if (ifi) printf("outdev = %u \n", ifi);
        ifi = nfq_get_physindev(nfa);
        if (ifi) printf("physindev = %u \n", ifi);
        ifi = nfq_get_physoutdev(nfa);
        if (ifi) printf("physoutdev = %u \n", ifi);
    }
    printf("len = %d \niphdr = %d \nipaddr : %u.%u.%u.%u ->", pdataLen, iphdrp->ihl<<2, IPQUAD(iphdrp->saddr));
    printf(" %u.%u.%u.%u \nprotocol = %s\n", IPQUAD(iphdrp->daddr), getprotobynumber(iphdrp->protocol)->p_name);
    // printf(" ipsum %hu", ip_checksum(iphdrp));
#endif
    /* 打印出和终端大小一样的框框 */
    for (i = 0; i < size.ws_col; i++)
        printf("*");
    // 设置裁定
    return nfq_set_verdict(qh, id, NF_ACCEPT, (u_int32_t)pdataLen, pdata);
}

int nfq_create_queue_run(int queue_num)
{
    struct nfq_handle *h;
    struct nfq_q_handle *qh;
    struct nfnl_handle *nh;
    int fd;
    int rv;
    char buf[4096];
    // 打开nfq_handle
    assert((h = nfq_open()) != NULL);
    // 先解开和AF_INET的绑定
    assert(nfq_unbind_pf(h, AF_INET) == 0);
    // 绑定到AF_INET
    assert(nfq_bind_pf(h, AF_INET) == 0);
    // 建立nfq_q_handle, 号码是 80 , 回调函数是cb
    // 可建立多个queue,用不同的号码区分即可
    // 此处的号码 nfq_create_queue 的第 2 个参数 80 与后来的设置 iptables 的那个队列好是需要一一对应的
    assert((qh = nfq_create_queue(h, queue_num, &cb, NULL)) != NULL);
    // 设置数据拷贝模式, 全包拷贝
    assert(nfq_set_mode(qh, NFQNL_COPY_PACKET, 0xffff) == 0);

    fd = nfq_fd(h);
    // 从netlink套接字接收数据
    while ((rv = recv(fd, buf, sizeof(buf), 0)) && rv >= 0)
    {
        // 处理数据,最终会调用到相应的回调函数
        nfq_handle_packet(h, buf, rv);
    }
    // 释放队列
    nfq_destroy_queue(qh);

    nfq_close(h);
    return 0;
}
