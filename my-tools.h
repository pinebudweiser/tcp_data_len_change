#ifndef MYTOOLS_H
#define MYTOOLS_H
#include<stdint.h>

typedef struct PseudoHeader{
    uint32_t src_addr;
    uint32_t dst_addr;
    uint8_t reserved=0;
    uint8_t protocol;
    uint16_t tcp_length;
}PSEUDO_HEADER;

// This tool class use for IP, TCP, UDP Protocol.
class MyTool{
public:
    MyTool(){
        packet_ = 0;
        len_ = 0;
    }
    void Init(uint8_t* packet, uint32_t len)
    {
        packet_ = packet;
        len_ = len;
    }
    uint16_t GetCheckSum();
private:
    uint8_t* packet_;
    uint32_t len_;
};
#endif // MYTOOLS_H
