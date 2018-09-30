#ifndef FLOWMANAGER_H
#define FLOWMANAGER_H

#include <iostream>
#include <stdint.h>

class FlowManager{
private:
    uint32_t src_ip_;
    uint32_t dst_ip_;
    uint16_t src_port_;
    uint16_t dst_port_;
    uint16_t data_len_;
public:
    void init(uint32_t src_ip_value, uint32_t dst_ip_value, uint16_t src_port_value, uint16_t dst_port_value)
    {
        src_ip_ = src_ip_value;
        dst_ip_ = dst_ip_value;
        src_port_ = src_port_value;
        dst_port_ = dst_port_value;
        is_change_ = false;
    }
    void reverse()
    {
        FlowManager temp;

        temp.init(this->src_ip_, this->dst_ip_, this->src_port_, this->dst_port_);
        this->src_ip_ = temp.dst_ip_;
        this->dst_ip_ = temp.src_ip_;
        this->src_port_ = temp.dst_port_;
        this->dst_port_ = temp.src_port_;
    }
    void ChangeValue(bool is_change){
        is_change_ = is_change;
    }
    bool operator ==(FlowManager* arg1){
        uint8_t flag = 0;
        if(this->dst_ip_ == arg1->dst_ip_) flag++;
        if(this->src_ip_ == arg1->src_ip_) flag++;
        if(this->dst_port_ == arg1->dst_port_) flag++;
        if(this->src_port_ == arg1->src_port_) flag++;
        if(this->is_change_ == arg1->is_change_) flag++;

        return flag == 5 ? true : false;
    }
};


#endif // FLOWMANAGER_H
