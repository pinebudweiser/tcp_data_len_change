#include "protocols.h"

uint8_t MyIPV4::GetHeaderLength(){
    return (packet_->ip_hl << 2);
}
uint16_t MyIPV4::GetIpTotalLength(){
    return ntohs(packet_->ip_len);
}
uint8_t MyIPV4::GetVersion(){
    return packet_->ip_v;
}
uint8_t MyIPV4::GetProtocol(){
    return packet_->ip_p;
}
uint32_t MyIPV4::GetSourceIp(){
    return packet_->ip_src.s_addr;
}
uint32_t MyIPV4::GetDestinationIp(){
    return packet_->ip_dst.s_addr;
}
void MyIPV4::SetCheckSum(){
    MyTool::Init((uint8_t*)packet_, GetHeaderLength()); // Current Packet reload
    packet_->ip_sum = 0;
    packet_->ip_sum = htons(MyTool::GetCheckSum());
}
void MyIPV4::SetTotalLength(uint16_t add_value){
   packet_->ip_len = htons(GetIpTotalLength() + add_value);
}

void MyTCP::InitPseudoHeader(MyIPV4& temp){
    pseudo_data_.src_addr = temp.GetSourceIp();
    pseudo_data_.dst_addr = temp.GetDestinationIp();
    pseudo_data_.reserved = 0;
    pseudo_data_.protocol = temp.GetProtocol();
    pseudo_data_.tcp_length = htons(GetHeaderLength() + data_length_);
}
uint16_t MyTCP::GetTcpDataLength(){
    return data_length_;
}
uint16_t MyTCP::GetHeaderLength(){
    return (packet_->th_off << 2);
}
char* MyTCP::GetPayload(){
    return (char*)((uint8_t*)packet_ + MyTCP::GetHeaderLength());
}
void MyTCP::SetCheckSum(){
    uint32_t result = 0;
    uint8_t carry = 0;

    packet_->th_sum = 0; // You have must initialize before Init function.
    MyTool::Init((uint8_t*)packet_, GetHeaderLength() + GetTcpDataLength()); // set TCP Header + TCP Data
    result = htons(MyTool::GetCheckSum());
    MyTool::Init((uint8_t*)&pseudo_data_, sizeof(PSEUDO_HEADER)); // set pseudo header
    result += htons(MyTool::GetCheckSum());
    /* calculate carry */
    carry = (result & 0xFF0000) >> 16;
    result += carry;
    packet_->th_sum = (uint16_t)result;
}
uint16_t MyTCP::GetSourcePort(){
    return packet_->th_sport;
}
uint16_t MyTCP:: GetDestinationPort(){
    return packet_->th_dport;
}
uint32_t MyTCP::GetSequenceNumber(){
    return packet_->th_ack;
}
uint32_t MyTCP::GetAcknownledgeNumber(){
    return packet_->th_seq;
}
void MyTCP::SetSequenceNumber(uint32_t value){
    packet_->th_seq += htons(value);
}
void MyTCP::SetAcknownledgeNumber(uint32_t value){
    packet_->th_ack += htons(value);
}
