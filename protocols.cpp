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
    return ntohl(packet_->ip_src.s_addr);
}
uint32_t MyIPV4::GetDestinationIP(){
    return ntohl(packet_->ip_dst.s_addr);
}
void MyIPV4::SetCheckSum(){
    packet_->ip_sum = htons(MyTool::GetCheckSum());
}

void MyTCP::InitPseudoHeader(MyIPV4& temp){
    pseudo_data_.src_addr = temp.GetSourceIP();
    pseudo_data_.dst_addr = temp.GetDestinationIP();
    pseudo_data_.reserved = 0;
    pseudo_data_.protocol = temp.GetProtocol();
    pseudo_data_.tcp_length = header_length_ + data_length_ + sizeof(PSEUDO_HEADER);
}
