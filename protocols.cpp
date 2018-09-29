#include "protocols.h"""

uint8_t MyIPV4::GetHeaderLength(){
    return header_length_;
}
uint16_t MyIPV4::GetIPLength(){
    return data_length_;
}
uint8_t MyIPV4::GetVersion(){
    return packet_->ip_v;
}
uint8_t MyIPV4::GetProtocol(){
    return packet_->ip_p;
}
