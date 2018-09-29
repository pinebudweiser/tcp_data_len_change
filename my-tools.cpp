#include "my-tools.h"

uint16_t MyTool::GetCheckSum()
{
    uint32_t result = 0;
    uint8_t carry = 0;
    int i = 0;

    for(i = 0; i < len_-1; i+=2)
        result += ((packet_[i] << 8) + (packet_[i+1]));
    if(len_ % 2) // if odd num
        result += packet_[i] << 8;
    carry = (result & 0xFF0000) >> 16;
    result += carry;
    result = ~result;
    return (uint16_t)result;
}
