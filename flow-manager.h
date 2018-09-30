#ifndef FLOWMANAGER_H
#define FLOWMANAGER_H

#include <iostream>
#include <stdint.h>
#include <arpa/inet.h>
#include "protocols.h"

class FlowManager{
private:
    uint32_t src_ip_;
    uint32_t dst_ip_;
    uint16_t src_port_;
    uint16_t dst_port_;
    //uint32_t sequence_number_;
    //uint32_t acknowledge_number_;
public:
    uint32_t sequence_number_;
    uint32_t acknowledge_number_;
    // Only flow manager use little endian. because other class calculating checksum. They are using big-endian.
    FlowManager();
    FlowManager(MyIPV4& ref_ip, MyTCP& ref_tcp){
        src_ip_ = ntohl(ref_ip.GetSourceIP());
        dst_ip_ = ntohl(ref_ip.GetDestinationIP());
        src_port_ = ntohs(ref_tcp.GetSourcePort());
        dst_port_ = ntohs(ref_tcp.GetDestinationPort());
        sequence_number_ = ntohl(ref_tcp.GetSequenceNumber());
        acknowledge_number_ = ntohl(ref_tcp.GetAcknownledgeNumber());
    }
    void init(MyIPV4& ref_ip, MyTCP& ref_tcp)
    {
        src_ip_ = ntohl(ref_ip.GetSourceIP());
        dst_ip_ = ntohl(ref_ip.GetDestinationIP());
        src_port_ = ntohs(ref_tcp.GetSourcePort());
        dst_port_ = ntohs(ref_tcp.GetDestinationPort());
        sequence_number_ = ntohl(ref_tcp.GetSequenceNumber());
        acknowledge_number_ = ntohl(ref_tcp.GetAcknownledgeNumber());
    }
    void reverse(MyIPV4& ref_ip, MyTCP& ref_tcp)
    {
        FlowManager temp(ref_ip, ref_tcp);

        this->src_ip_ = temp.dst_ip_;
        this->dst_ip_ = temp.src_ip_;
        this->src_port_ = temp.dst_port_;
        this->dst_port_ = temp.src_port_;
        this->sequence_number_ = temp.acknowledge_number_;
        this->acknowledge_number_ = temp.sequence_number_;
    }
    bool operator ==(FlowManager* arg1){
        uint8_t flag = 0;
        if(this->dst_ip_ == arg1->dst_ip_) flag++;
        if(this->src_ip_ == arg1->src_ip_) flag++;
        if(this->dst_port_ == arg1->dst_port_) flag++;
        if(this->src_port_ == arg1->src_port_) flag++;
        if((this->sequence_number_ == arg1->sequence_number_) ||
                (this->acknowledge_number_ == arg1->acknowledge_number_) ) flag++;

        return (flag == 5) ? true : false;
    }
};

#endif // FLOWMANAGER_H
