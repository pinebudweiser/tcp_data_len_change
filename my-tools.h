#ifndef MYTOOLS_H
#define MYTOOLS_H
#include<stdint.h>



// This tool class use for IP, TCP, UDP Protocol.
class MyTool{
public:
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
