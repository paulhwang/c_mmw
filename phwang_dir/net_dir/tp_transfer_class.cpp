/*
  Copyrights reserved
  Written by Paul Hwang
  File name: tp_transfer_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "tp_transfer_class.h"

TpTransferClass::TpTransferClass (int socket_val,
                                  void (*receive_callback_val)(void *, void *, void *),
                                  void *receive_object_val,
                                  char const *who_val)
{
    memset(this, 0, sizeof(*this));
    this->theSocket = socket_val;
    this->theReceiveCallback = receive_callback_val;
    this->theReceiveObject = receive_object_val;
    this->theWho = who_val;
    this->setMaxDataSize();

    this->theReceiveQueue = phwangMallocSuspendedQueue(TP_TRANSFER_CLASS_RECEIVE_QUEUE_SIZE);
    this->theTransmitQueue = phwangMallocSuspendedQueue(TP_TRANSFER_CLASS_TRANSMIT_QUEUE_SIZE);

    if (1) { /* debug */
        char s[128];
        sprintf(s, "init for (%s) %d", this->theWho, this->maxDataSize());
        this->logit("TpTransferClass", s);
    }
}

TpTransferClass::~TpTransferClass (void)
{
}

void TpTransferClass::startThreads (int index_val)
{
    if (1) { /* debug */
        char s[128];
        sprintf(s, "threads started for (%s) index=%i", this->theWho, index_val);
        this->logit("startThreads", s);
    }

    this->theIndex = index_val;
    this->startReceiveThread2();
    this->startReceiveThread(this->theSocket);
    this->startTransmitThread(this->theSocket);
}

void TpTransferClass::logit (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangLogit(s, str1_val);
}

void TpTransferClass::abend (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangAbend(s, str1_val);
}

