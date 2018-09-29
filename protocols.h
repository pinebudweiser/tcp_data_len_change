#ifndef PROTOCOLS_H
#define PROTOCOLS_H

#include<stdint.h>
#include <libnet.h>

/* libnet struct typedefing */
typedef struct libnet_ipv4_hdr IP;
typedef struct libnet_tcp_hdr TCP;

class MyIPV4{
public:
    MyIPV4(uint8_t* packet){
        packet_ = (IP*)packet;
        header_length_ = (packet_->ip_hl << 2);
        data_length_ = ntohs(packet_->ip_len);
    }
    uint8_t GetHeaderLength();
    uint16_t GetIPLength();
    uint8_t GetVersion();
    uint8_t GetProtocol();
    friend class MyTCP;
private:
    uint8_t header_length_;
    uint16_t data_length_;
    IP* packet_;
};

class MyTCP{
public:
    MyTCP(uint8_t* packet, MyIPV4& temp){
        packet_ = (TCP*)(packet + (temp.packet_->ip_hl << 2));
        header_length_ = (packet_->th_x2 << 2);
        data_length_ = temp.GetIPLength() - (temp.GetHeaderLength() + header_length_);
    }
    uint16_t GetTCPLength(){
        return data_length_;
    }
private:
    TCP* packet_;
    uint8_t header_length_;
    uint16_t data_length_;
};

#endif // PROTOCOLS_H
