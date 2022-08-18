/*
  Copyrights reserved
  Written by Paul Hwang
  File name: tp_server_class.cpp
*/

#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <pwd.h>
#include "tp_phwang_logo.h"
#include "tp_transfer_class.h"
#include "../../phwang_dir/phwang.h"
#include "tp_server_class.h"

#define MAXHOSTNAME 32
#define BACKLOG 5

TpServerClass::TpServerClass (
                    void *caller_object_val,
                    unsigned short port_val,
                    void (*accept_callback_func_val)(void *, void *),
                    void *accept_callback_parameter_val,
                    void (*receive_callback_func_val)(void *, void *, void *),
                    void *receive_callback_parameter_val,
                    char const *who_val)

{
    memset(this, 0, sizeof(*this));
    this->theCallerObject = caller_object_val;
    this->thePort = port_val;
    this->theAcceptCallbackFunc = accept_callback_func_val;
    this->theReceiveCallbackFunc = receive_callback_func_val;
    this->theAcceptCallbackParameter = accept_callback_parameter_val;
    this->theReceiveCallbackParameter = receive_callback_parameter_val;
    this->theWho = who_val;
    this->theTpTransferObjectIndex = 1;

    if (0) { /* debug */
        char s[128];
        sprintf(s, "init by (%s)", who_val);
        this->logit("TpServerClass", s);
    }
}

TpServerClass::~TpServerClass (void)
{
}

void *transportServerThreadFunction (void *tp_server_object_val)
{
    ((TpServerClass *) tp_server_object_val)->serverThreadFunction(0);
}

void TpServerClass::startServerThread (void)
{
    if (0) { /* debug */
        char s[128];
        sprintf(s, "for (%s)", this->theWho);
        this->logit("startServerThread", s);
    }

    int r = pthread_create(&this->theServerThread, 0, transportServerThreadFunction, this);
    if (r) {
        printf("Error - startServerThread() return code: %d\n", r);
        return;
    }
}

void TpServerClass::serverThreadFunction (void *data_val)
{
    char const *func_name_ = "serverThreadFunction";
    char localhost[MAXHOSTNAME + 1];
    struct servent *sp;
    int s, data_socket;
    struct hostent *hp;
    int opt = 1;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    if (0) { /* debug */
        char s[128];
        sprintf(s, "starts for (%s)", this->theWho);
        this->logit(func_name_, s);
    }

    if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        this->logit(func_name_, "open socket error");
        return;
    }

    if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        this->logit(func_name_, "setsockopt error");
        return;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(this->thePort);

    if (bind(s, (struct sockaddr *)&address, sizeof(address)) < 0) {
        this->logit(func_name_, "bind error");
        return;
    }

    while (1) {
        if (0) { /* debug */
            char s[128];
            sprintf(s, "listening for (%s)", this->theWho);
            this->logit(func_name_, s);
        }

        listen(s, BACKLOG);

        if (1) { /* debug */
            char s[128];
            sprintf(s, "accepting for (%s)", this->theWho);
            this->logit(func_name_, s);
        }

        if ((data_socket = accept(s, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            this->logit(func_name_, "accept error");
            return;
        }

        if (1) { /* debug */
            char s[128];
            sprintf(s, "accepted for (%s) port=%d", this->theWho, this->thePort);
            this->logit(func_name_, s);
        }

        char data[strlen(TP_PHWANG_LOGO) + 16];
        int length = read(data_socket, data, strlen(TP_PHWANG_LOGO) + 8);
        if (length >= 0) {
            data[length] = 0;
        }
        if ((length != strlen(TP_PHWANG_LOGO)) || (strcmp(data, TP_PHWANG_LOGO))) {
            if (1) { /* debug */
                char s[128];
                sprintf(s, "### Attack: (%s) port=%d data_length=%d data=%s", this->theWho, this->thePort, length, data);
                this->logit(func_name_, s);
            }
            close(data_socket);
            continue;
        }

        TpTransferClass *tp_transfer_object = new TpTransferClass(data_socket, this->theReceiveCallbackFunc, this->theCallerObject, this->theWho);
        tp_transfer_object->startThreads(this->theTpTransferObjectIndex);
        this->theTpTransferObjectIndex++;
        this->theAcceptCallbackFunc(this->theCallerObject, tp_transfer_object);
    }

    //free(data_val);
}


void TpServerClass::logit (char const *str0_val, char const *str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangLogit(s, str1_val);
}

void TpServerClass::abend (char const *str0_val, char const *str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangAbend(s, str1_val);
}

