#include "protocols.h"

uint8_t MyIPV4::GetHeaderLength(){
    return (packet_->ip_hl << 2);
}
uint16_t MyIPV4::GetDataLength(){
    return ntohs(packet_->ip_len);
}
uint8_t MyIPV4::GetVersion(){
    return packet_->ip_v;
}
uint8_t MyIPV4::GetProtocol(){
    return packet_->ip_p;
}
uint32_t MyIPV4::GetSourceIP(){
    return packet_->ip_src.s_addr;
}
uint32_t MyIPV4::GetDestinationIP(){
    return packet_->ip_dst.s_addr;
}
void MyIPV4::SetCheckSum(){
    packet_->ip_sum = 0;
    packet_->ip_sum = htons(MyTool::GetCheckSum());
}
void MyIPV4::SetTotalLength(uint16_t add_value){
   packet_->ip_len = htons(GetDataLength() + add_value);
}

void MyTCP::InitPseudoHeader(MyIPV4& temp){
    pseudo_data_.src_addr = temp.GetSourceIP();
    pseudo_data_.dst_addr = temp.GetDestinationIP();
    pseudo_data_.reserved = 0;
    pseudo_data_.protocol = temp.GetProtocol();
    pseudo_data_.tcp_length = htons(header_length_ + data_length_);
}
uint16_t MyTCP::GetLength(){
    return data_length_;
}
uint16_t MyTCP::GetHeaderLength(){
    return header_length_;
}
char* MyTCP::GetPayload(){
    return (char*)((uint8_t*)packet_ + header_length_);
}
void MyTCP::SetCheckSum(){
    packet_->th_sum = 0; // You have must initialize before Init function.
    MyTool::Init((uint8_t*)&pseudo_data_, (uint8_t*)packet_,
                 sizeof(PSEUDO_HEADER), header_length_ + data_length_); // dynamic allocation..
    packet_->th_sum = htons(MyTool::GetCheckSum());
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
