#ifndef NFQMANAGER_H
#define NFQMANAGER_H

#include <stdio.h>
#include <linux/netfilter.h>
#include <libnetfilter_queue/libnetfilter_queue.h>

/* nfq struct typedefing */
typedef struct nfq_q_handle nfq_q_handle;
typedef struct nfgenmsg nfgenmsg;
typedef struct nfq_data nfq_data;
typedef struct nfq_handle nfq_handle;
typedef struct nfq_q_handle nfq_q_handle;
typedef struct nfqnl_msg_packet_hdr nfqnl_msg_packet_hdr;

class NetFilterQueueManager{
public:
    NetFilterQueueManager(nfq_callback* callback){
        handle_open_ = nfq_open();
        if(!handle_open_)
            printf("[+] nfq_open failed..\n");
        handle_crt_ = nfq_create_queue(handle_open_, 0, callback, NULL);
        if (!handle_crt_)
            printf("[+] nfq_create_queue failed..\n");
        if(nfq_set_mode(handle_crt_, NFQNL_COPY_PACKET, 0xFFFF))
            printf("[+] nfq_set_mode failed..\n");
        descriptor_ = nfq_fd(handle_open_);
        if (!descriptor_)
            printf("[+] descriptor is null..\n");
    }
    ~NetFilterQueueManager(){
        nfq_destroy_queue(handle_crt_);
        nfq_close(handle_open_);
    }
    int GetDescritpor(){
        return descriptor_;
    }
    nfq_handle* GetNFQHandle(){
        return handle_open_;
    }
private:
    nfq_handle* handle_open_;
    nfq_q_handle* handle_crt_;
    int descriptor_;
};

#endif // NFQMANAGER_H
