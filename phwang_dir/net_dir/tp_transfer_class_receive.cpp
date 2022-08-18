/*
  Copyrights reserved
  Written by Paul Hwang
  File name: tp_transfer_receive.cpp
*/

#include <stdlib.h>
#include <pthread.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <pwd.h>
#include "../../phwang_dir/phwang.h"
#include "tp_transfer_class.h"

void TpTransferClass::receiveThreadFunction(int socket_val)
{
    char const *func_name_ = "receiveThreadFunction";

    while (1) {
        char *data = (char *) phwangMalloc(TP_TRANSFER_CLASS_RECEIVE_BUFFER_SIZE + 32, "TpR1");

        int length = read(socket_val, data, TP_TRANSFER_CLASS_RECEIVE_BUFFER_SIZE);
        if (length > 0) {
            data[length] = 0;
            
            if (0) { /* debug */
                char s[128];
                sprintf(s, "(%s) data=%s len=%d", this->theWho, data, length);
                this->logit(func_name_, s);
            }

            if ((*data != '{') && (*data != '[')) {
                if (1) { /* debug */
                    char s[2000];
                    sprintf(s, "(%s) data=%s len=%d", this->theWho, data, length);
                    this->logit(func_name_, s);
                }
                this->abend("receiveThreadFunction: wrong header", data);
                continue;
            }

            phwangEnqueue(this->theReceiveQueue, data);
        }
        else {
            usleep(10);
        }
    }
}

void *tpTranferReceiveThreadFunction (void *data_val)
{
    int socket = ((tp_transfer_thread_parameter *) data_val)->socket;
    TpTransferClass *tp_transfer_object = ((tp_transfer_thread_parameter *) data_val)->tp_transfer_object;
    phwangFree(data_val, "tpTranferReceiveThreadFunction");

    tp_transfer_object->receiveThreadFunction(socket);
}

void TpTransferClass::startReceiveThread (int socket_val)
{
    tp_transfer_thread_parameter *data = (tp_transfer_thread_parameter *) phwangMalloc(sizeof(tp_transfer_thread_parameter), "TpRh");
    data->socket = socket_val;
    data->tp_transfer_object = this;

    this->debug(false, "startReceiveThread", "");

    int r = pthread_create(&this->theReceiveThread, 0, tpTranferReceiveThreadFunction, data);
    if (r) {
        printf("Error - startReceiveThread() return code: %d\n", r);
        return;
    }
}

/**************************************************************************************************************/
/**************************************************************************************************************/
/**************************************************************************************************************/

void TpTransferClass::receiveThreadFunction2 (void)
{
    char const *func_name_ = "receiveThreadFunction2";

    while (1) {
        char *raw_data = (char *) phwangDequeue(this->theReceiveQueue, "TpTransferClass::receiveThreadFunction2()");
        if (raw_data) {
            int raw_length = strlen(raw_data);
            int length;
            int length1;
            char *data;

            if (0) { /* debug */
                char s[128];
                sprintf(s, "(%s) data=%s", this->theWho, raw_data);
                this->logit(func_name_, s);
            }

            if (raw_data[0] == '{') {
                length = raw_length - (1 + TP_TRANSFER_CLASS_DATA_LENGTH_SIZE + 1);
                length1 = phwangDecodeNumber(&raw_data[1], TP_TRANSFER_CLASS_DATA_LENGTH_SIZE);
                if (length != length1) {
                    char s[128];
                    sprintf(s, "(%s) length not match!!! data=%s len=%d %d", this->theWho, raw_data, length, length1);
                    this->abend(func_name_, s);
                }

                data = (char *) phwangMalloc(length + 32, "TpR3");
                memcpy(data, &raw_data[1 + TP_TRANSFER_CLASS_DATA_LENGTH_SIZE], length);
                data[length] = 0;
             }
            else {
                if (1) { /* debug */
                    char s[2000];
                    sprintf(s, "(%s) data=%s len=%d", this->theWho, raw_data, strlen(raw_data));
                    this->logit(func_name_, s);
                }
                this->abend("receiveThreadFunction2: wrong header", raw_data);
                continue;
            }

            phwangFree(raw_data, "TpTransferClass::receiveThreadFunction2");
            this->receiveCallback()(this, this->theReceiveObject, data);
        }
    }
}

void *tpTranferReceiveThreadFunction2 (void *this_val)
{
    ((TpTransferClass *)this_val)->receiveThreadFunction2();
}

void TpTransferClass::startReceiveThread2 (void)
{
    this->debug(false, "startReceiveThread2", "create receiveThread");

    int r = pthread_create(&this->theReceiveThread2, NULL, tpTranferReceiveThreadFunction2, this);
    if (r) {
        printf("Error - pthread_create() return code: %d\n", r);
        return;
    }
}
