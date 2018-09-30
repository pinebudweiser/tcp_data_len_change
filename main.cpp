#include <iostream>
#include <string>
#include <map>
#include "protocols.h"
#include "nfq-manager.h"

using namespace std;

int QueueProcesser(nfq_q_handle *crt_handle, nfgenmsg *nfmsg, nfq_data *packet_handler, void *data){
    uint8_t* packet;
    uint32_t pkt_len;
    nfqnl_msg_packet_hdr *packet_header;
    std::string payload;
    int id, hook_type;
    // std::map<key,value> -> key is flow and value is pair<SEQ, ACK>.

    packet_header = nfq_get_msg_packet_hdr(packet_handler);
    if (packet_header){
        id = ntohl(packet_header->packet_id);
        hook_type = packet_header->hook;
    }
    pkt_len = nfq_get_payload(packet_handler, &packet);

    MyIPV4 ip_instance(packet);

    if(ip_instance.GetVersion() == IPPROTO_IPIP){
        switch(ip_instance.GetProtocol()){
            case IPPROTO_TCP:
                MyTCP tcp_instance(packet, ip_instance);
                if(tcp_instance.GetLength())
                {
                    payload = tcp_instance.GetPayload();
                    std::string::size_type pos = 0;
                    if((pos = payload.find("hello_world")) != string::npos){
                        memcpy(tcp_instance.GetPayload() + pos, "HELLO_WORLD", 11);
                        tcp_instance.SetCheckSum();
                    }
                    printf("tcp_instance.GetTCPLength() = %d\n", tcp_instance.GetLength());
                }
            break;
        }
    }
    return nfq_set_verdict(crt_handle, id, NF_ACCEPT, pkt_len, packet);
}

int main(int argc, char** argv){
    char buf[4096];
    int pkt_len;
    int nfq_descriptor;
    NetFilterQueueManager netfilter_instance(&QueueProcesser);
    uint8_t* packet;
    nfq_handle* nfq_open_handle;

    if(argc != 3){
        printf("Usage: tcp_data_len_change <from string> <to string>\n");
        return 0;
    }
    nfq_descriptor = netfilter_instance.GetDescritpor();
    nfq_open_handle = netfilter_instance.GetNFQHandle();

    while(true){
        if((pkt_len = recv(nfq_descriptor, buf, sizeof(buf), 0)) >= 0){
            nfq_handle_packet(nfq_open_handle, buf, pkt_len);
            continue;
        }
        if(pkt_len < 0){
            printf("[>] Packet loss!\n");
            continue;
        }
    }
    return 0;
}
