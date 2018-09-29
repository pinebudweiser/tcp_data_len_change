#include <iostream>
#include <map>
#include <libnet.h>
#include "nfq-manager.h"

using namespace std;

int queue_processor(nfq_q_handle *CrtHandle, nfgenmsg *nfmsg,
                    nfq_data *packet_handler, void *data){
    uint8_t* packet;
    uint32_t pktLen;
    nfqnl_msg_packet_hdr *packetHeader;
    int id;

    packetHeader = nfq_get_msg_packet_hdr(packet_handler);
    if (packetHeader){
        id = ntohl(packetHeader->packet_id);
    }

    return nfq_set_verdict(CrtHandle, id, NF_ACCEPT, pktLen, packet);
}

int main(int argc, char** argv){
    char buf[4096];
    int pkt_len;
    int nfqDescriptor;
    NFQManager netfilter_instance(&queue_processor);
    uint8_t* packet;
    nfq_handle* nfqOpenHandle;

    if(argc != 3){
        printf("Usage: tcp_data_len_change <from string> <to string>\n");
        return 0;
    }
    nfqDescriptor = netfilter_instance.GetDescritpor();
    nfqOpenHandle = netfilter_instance.GetNFQHandle();

    while(true)
    {
        if((pkt_len = recv(nfqDescriptor, buf, sizeof(buf), 0)) >= 0)
        {
            nfq_handle_packet(nfqOpenHandle, buf, pkt_len);
            continue;
        }
        if(pkt_len < 0)
        {
            printf("[Err] Packet loss!\n");
            continue;
        }
    }
    return 0;
}
