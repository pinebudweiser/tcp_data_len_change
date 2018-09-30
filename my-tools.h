#ifndef MYTOOLS_H
#define MYTOOLS_H
#include<stdint.h>
#include<stdlib.h>
#include<string.h>

// This tool class use for IP, TCP, UDP Protocol.
class MyTool{
public:
    MyTool(){}
    void Init(uint8_t* packet, uint32_t len)
    {
        packet_ = packet;
        len_ = len;
    }
    void Init(uint8_t* packet1, uint8_t* packet2, uint32_t len1, uint32_t len2){
        packet_ = (uint8_t*)malloc((len1+len2));
        memcpy(packet_, packet1, len1);
        memcpy(packet_ + len1, packet2, len2);
        len_ = len1 + len2;
    }
    uint16_t GetCheckSum();
private:
    uint8_t* packet_;
    uint32_t len_;
};
#endif // MYTOOLS_H
