#ifndef PROTOCOLS_H
#define PROTOCOLS_H

#include<stdint.h>
#include <libnet.h>
#include "my-tools.h"

/* libnet struct typedefing */
typedef struct libnet_ipv4_hdr IP;
typedef struct libnet_tcp_hdr TCP;

typedef struct PseudoHeader{
    uint32_t src_addr;
    uint32_t dst_addr;
    uint8_t reserved=0;
    uint8_t protocol;
    uint16_t tcp_length;
}PSEUDO_HEADER;

class MyIPV4 : public MyTool{
public:
    MyIPV4(uint8_t* packet)
    {
        packet_ = (IP*)packet;
    }
    uint8_t GetHeaderLength();
    uint8_t GetVersion();
    uint8_t GetProtocol();
    uint16_t GetIpTotalLength();
    uint32_t GetSourceIp();
    uint32_t GetDestinationIp();
    void SetCheckSum();
    void SetTotalLength(uint16_t add_value); // recalculate function
private:
    IP* packet_;
};

class MyTCP : public MyTool{
public:
    MyTCP(uint8_t* packet, MyIPV4& temp)
    {
        packet_ = (TCP*)(packet + temp.GetHeaderLength()); // TCP Header
        data_length_ = temp.GetIpTotalLength() - (temp.GetHeaderLength() + MyTCP::GetHeaderLength()); // TCP Data length
        InitPseudoHeader(temp);
    }
    uint16_t GetTcpDataLength();
    uint16_t GetHeaderLength();
    uint16_t GetSourcePort();
    uint16_t GetDestinationPort();
    uint32_t GetSequenceNumber();
    uint32_t GetAcknownledgeNumber();
    bool FindAckPacket(){
        return (packet_->th_flags == 0x10) ? true : false;
    }
    char* GetPayload();
    void SetCheckSum();
    void InitPseudoHeader(MyIPV4& temp);
private:
    TCP* packet_;
    PSEUDO_HEADER pseudo_data_;
    uint16_t data_length_;
};

#endif // PROTOCOLS_H
