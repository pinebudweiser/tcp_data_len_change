#include <iostream>
#include <string>
#include <map>
#include "protocols.h"
#include "nfq-manager.h"
#include "flow-manager.h"

using namespace std;

/* static variable */

static string from_string;
static string too_string;
static std::map<FlowManager*, uint16_t> input_data_map, output_data_map;

int QueueProcesser(nfq_q_handle *crt_handle, nfgenmsg *nfmsg, nfq_data *packet_handler, void *data){
    uint8_t* packet;
    uint32_t pkt_len;
    nfqnl_msg_packet_hdr *packet_header;
    std::string payload;
    FlowManager *output_flow, *input_flow;
    int id, hook_type;

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

                /* TODO : Flow supervise thread */
                if(hook_type == 1) // INPUT
                {
                    input_flow = (FlowManager*)malloc(sizeof(FlowManager));
                    input_flow->init(ip_instance, tcp_instance);
                    input_data_map.insert(std::pair<FlowManager*, uint16_t>(input_flow, tcp_instance.GetLength()));
                }
                if(hook_type == 3) // OUTPUT
                {
                    output_flow = (FlowManager*)malloc(sizeof(FlowManager));
                    output_flow->init(ip_instance, tcp_instance);
                    output_data_map.insert(std::pair<FlowManager*, uint16_t>(output_flow, tcp_instance.GetLength()));
                }
                /* TODO : Check data and Modifying Thread*/
                if(tcp_instance.GetLength())
                {
                    payload = tcp_instance.GetPayload();
                    std::string::size_type pos = 0;
                    if((pos = payload.find(from_string)) != string::npos){
                        // Find Itrator test
                        FlowManager temp_input_flow(ip_instance, tcp_instance);
                        temp_input_flow.reverse(ip_instance, tcp_instance);
                        std::map<FlowManager*, uint16_t>::iterator iter;
                        for(iter = output_data_map.begin(); iter != output_data_map.end(); iter++){
                            if(temp_input_flow == (*iter).first)
                            {
                                cout << "Test call!" << (*iter).second << endl;
                            }
                        }
                    }
                }
                /* TODO : Find ACK Packet Thread */
                /* TODO : Find FIN Packet Thread -> free (in/out)data_map*/
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
    nfq_handle* nfq_open_handle;

    if(argc != 3){
        printf("Usage: tcp_data_len_change <from string> <to string>\n");
        return 0;
    }
    from_string = argv[1];
    too_string = argv[2]; // to_string ambiguous errors
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
