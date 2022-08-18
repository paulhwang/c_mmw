/*
  Copyrights reserved
  Written by Paul Hwang
  File name: tp_connect.cpp
*/

#include <sys/socket.h>
#include <arpa/inet.h>
#include "../../phwang_dir/phwang.h"
#include "tp_phwang_logo.h"
#include "./tp_transfer_class.h"

#define PHWANG_TP_CONNECT_RETRY_MAX_COUNT 30

void *globalTpConnect (
                    unsigned long ip_addr_val, 
                    unsigned short port_val, 
                    void (*receive_callback_val)(void *, void *, void *), 
                    void *receive_object_val,
                    char const *who_val)
{
    char const *func_name_ = "globalTpConnect";
    int s;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};

    if (1) { /* debug */
        char s[128];
        sprintf(s, "starts for (%s)", who_val);
        phwangLogit(func_name_, s);
    }

    if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        phwangLogit(who_val, "tpConnect() open socket error");
        return 0;
    }
 
    memset(&serv_addr, '0', sizeof(serv_addr));
  
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port_val);
  
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        phwangLogit(who_val, "tpConnect() Invalid address/ Address not supported \n");
        return 0;
    }
  
    if (1) { /* debug */
        char s[128];
        sprintf(s, "connecing for (%s)", who_val);
        phwangLogit(func_name_, s);
    }

    int retry_count = PHWANG_TP_CONNECT_RETRY_MAX_COUNT;
    while (retry_count) {
        if (connect(s, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
            if (!retry_count--) {
                phwangLogit(who_val, "tpConnect() Failed \n");
                return 0;
            }
            else {
                phwangLogit(who_val, "tpConnect() retry-----");
                sleep(1);
            }
        }
        else {
            break;
        }
    }

    if (1) { /* debug */
        char s[128];
        sprintf(s, "connected for (%s)", who_val);
        phwangLogit(func_name_, s);
    }

    send(s, TP_PHWANG_LOGO , strlen(TP_PHWANG_LOGO) , 0);

    TpTransferClass *tp_transfer_object = new TpTransferClass(s, receive_callback_val, receive_object_val, who_val);
    tp_transfer_object->startThreads(0);
    return tp_transfer_object;
}
