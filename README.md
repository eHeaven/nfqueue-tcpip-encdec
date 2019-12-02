# nfqueue-tcpip-encdec

Using Netfilter_queue and nfnetlink to grab data, And then determine the encryption or decryption key by judging the value of tcphdr->resl from the acquired data.
# Todo ADD
Use one of the following command at terminal to add:

    - sudo iptables -I INPUT -j NFQUEUE --queue-num 80
    # 下面的命令会将发送给本机 80 端口的 TCP 数据包送往队列 80 :
    - iptables -A INPUT -p tcp --dport 80 -j NFQUEUE --queue-num 80

    # 下面的命令会将发送给 192.168.10.192 端口为 80 的 TCP 数据包送往队列 80 :
    - sudo iptables -I INPUT -d 192.168.10.192 -p tcp --dport 80 -j NFQUEUE --queue-num 80

    # 下面的命令会将发送给 192.168.10.192 所有的 TCP 数据包送往队列 80 :
    - sudo iptables -I INPUT -d 192.168.10.192 -p tcp --dport 80 -j NFQUEUE --queue-num 80

    # 下面的命令会将来自ip 192.168.10.141 端口为 80 的 TCP 数据包送往队列 80 :
    - sudo iptables -I INPUT -s 192.168.10.141 -p tcp --dport 80 -j NFQUEUE --queue-num 80

    # 下面的命令会将来自ip 192.168.10.141 所有的 TCP 数据包送往队列 80 :
    - sudo iptables -I INPUT -s 192.168.10.141 -p tcp  -j NFQUEUE --queue-num 80

    # 下面的命令会将所有的 TCP 数据包送往队列 80 :
    - sudo iptables -I INPUT -p tcp  -j NFQUEUE --queue-num 80
# Todo Delete
Use one of the commands corresponding to the ADD command on the terminal to delete.

    - sudo iptables -D INPUT -j NFQUEUE --queue-num 80
    - ... -D ...
    - ... -D ...
    - ...

