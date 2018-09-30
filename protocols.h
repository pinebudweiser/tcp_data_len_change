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
        MyTool::Init((uint8_t*)packet_, GetHeaderLength());
    }
    uint8_t GetHeaderLength();
    uint16_t GetDataLength();
    uint8_t GetVersion();
    uint8_t GetProtocol();
    uint32_t GetSourceIP();
    uint32_t GetDestinationIP();
    void SetCheckSum();
    IP* packet_;
private:
    //IP* packet_;
};

class MyTCP : public MyTool{
public:
    MyTCP(uint8_t* packet, MyIPV4& temp)
    {
        packet_ = (TCP*)(packet + temp.GetHeaderLength());
        header_length_ = (packet_->th_off << 2); //
        data_length_ = temp.GetDataLength() - (temp.GetHeaderLength() + header_length_);
        InitPseudoHeader(temp);
    }
    uint16_t GetLength();
    char* GetPayload();
    void SetCheckSum();
    void InitPseudoHeader(MyIPV4& temp);
    TCP* packet_;
    uint16_t data_length_;
    PSEUDO_HEADER pseudo_data_;
private:
    //TCP* packet_;
    //PSEUDO_HEADER pseudo_data_;
    uint8_t header_length_;
    //uint16_t data_length_;
};

#endif // PROTOCOLS_H
