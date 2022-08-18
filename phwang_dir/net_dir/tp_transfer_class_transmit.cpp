/*
  Copyrights reserved
  Written by Paul Hwang
  File name: tp_transfer_transmit.cpp
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <netinet/in.h>
#include "../../phwang_dir/phwang.h"
#include "tp_transfer_class.h"

void TpTransferClass::exportTransmitData (void *data_val)
{
    phwangEnqueue(this->theTransmitQueue, data_val);
}

void TpTransferClass::transmitThreadFunction(int socket_val)
{
    char const *func_name_ = "transmitThreadFunction";

    while (1) {
        char *data = (char *) phwangDequeue(this->theTransmitQueue, "TpTransferClass::transmitThreadFunction()");
        if (data) {
            if (0) { /* debug */
                char s[128];
                sprintf(s, "(%s) data=%s", this->theWho, data);
                this->logit(func_name_, s);
            }

            int length = strlen(data);
            char *ptr;
            char *buf = ptr = (char *) malloc(length + (1 + TP_TRANSFER_CLASS_DATA_LENGTH_SIZE + 1 + 1) + 32);

            if (length < 1400) {
                *ptr++ = '{';
                phwangEncodeNumber(ptr, length, TP_TRANSFER_CLASS_DATA_LENGTH_SIZE);
                ptr += TP_TRANSFER_CLASS_DATA_LENGTH_SIZE;
                strcpy(ptr, data);
                ptr += length;
                *ptr++ = '}';
                *ptr = 0;

                if (0) { /* debug */
                    char s[128];
                    sprintf(s, "(%s) buf=%s", this->theWho, buf);
                    this->logit(func_name_, s);
                }

                send(socket_val, buf , strlen(buf) , 0);
            }
            else {
                if (1) { /* debug */
                    char s[128];
                    sprintf(s, "(%s) length=%d", this->theWho, length);
                    this->logit(func_name_, s);
                }
                this->abend(func_name_, "*****LENGTH TOO BIG*****");
            }

            phwangFree(data, "TpTransferClass::transmitThreadFunction");
        }
    }
}

void *tpTransferTransmitThreadFunction (void *data_val)
{
    int socket = ((tp_transfer_thread_parameter *) data_val)->socket;
    TpTransferClass *tp_transfer_object = ((tp_transfer_thread_parameter *) data_val)->tp_transfer_object;
    phwangFree(data_val, "tpTransferTransmitThreadFunction");

    tp_transfer_object->transmitThreadFunction(socket);
}

void TpTransferClass::startTransmitThread (int socket_val)
{
    tp_transfer_thread_parameter *data = (tp_transfer_thread_parameter *) phwangMalloc(sizeof(tp_transfer_thread_parameter), "TpTh");
    data->socket = socket_val;
    data->tp_transfer_object = this;

    this->debug(false, "startTransmitThread", "");

    int r = pthread_create(&this->theTransmitThread, 0, tpTransferTransmitThreadFunction, data);
    if (r) {
        printf("Error - startTransmitThread() return code: %d\n", r);
        return;
    }
}
