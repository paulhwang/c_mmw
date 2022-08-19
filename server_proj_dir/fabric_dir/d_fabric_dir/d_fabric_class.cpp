/*
  Copyrights reserved
  Written by Paul Hwang
  File name: d_fabric_class.cpp
*/

#include <sys/socket.h>
#include "../../../phwang_dir/phwang.h"
#include "../../../phwang_dir/net_dir/tp_transfer_class.h"
#include "../../protocol_dir/net_port_protocol.h"
#include "../../protocol_dir/web_fabric_protocol.h"
#include "d_fabric_class.h"
#include "../fabric_class.h"
#include "../u_fabric_dir/u_fabric_class.h"

DFabricClass::DFabricClass (FabricClass *fabric_object_val)
{
    memset(this, 0, sizeof(DFabricClass));
    this->theFabricObject = fabric_object_val;
    this->setTimeStampString();
    this->startNetServer();

    this->debug(true, "DFabricClass", "init");
}

DFabricClass::~DFabricClass (void)
{
}

void dFabricTpServerAcceptFunction (void *d_fabric_object_val, void *tp_transfer_object_val) {
    phwangLogit("Golbal::dFabricTpServerAcceptFunction", "accepted (http client)");
    ((DFabricClass *) d_fabric_object_val)->exportedNetAcceptFunction(tp_transfer_object_val);
}

void DFabricClass::exportedNetAcceptFunction (void *tp_transfer_object_val)
{
    send(((TpTransferClass *)tp_transfer_object_val)->socket(), this->timeStampString() , strlen(this->timeStampString()) , 0);
}

void dFabricTpReceiveDataFunction (void *tp_transfer_object_val, void *d_fabric_object_val, void *data_val) {
    if (0) { /* debug */
        if (*((char *)data_val) != WEB_FABRIC_PROTOCOL_COMMAND_IS_GET_LINK_DATA) {
            char s[128];
            sprintf(s, "%s index=%d", (char *) data_val, ((TpTransferClass *) tp_transfer_object_val)->index());
            phwangLogit("Golbal::dFabricTpReceiveDataFunction", s);
        }
    }

    ((DFabricClass *) d_fabric_object_val)->exportedParseFunction(tp_transfer_object_val, (char *) data_val);
    phwangFree(data_val, "dFabricTpReceiveDataFunction");
}

void DFabricClass::startNetServer (void)
{
    this->theTpServerObject = phwangMallocTpServer(this, HTTP_FABRIC_PROTOCOL_TRANSPORT_PORT_NUMBER, dFabricTpServerAcceptFunction, this, dFabricTpReceiveDataFunction, this, this->objectName());
}

void DFabricClass::setTimeStampString (void)
{
    time_t seconds = time(NULL);
    int time_stamp = (int) ((seconds - 1642858200) / 60);
    phwangEncodeNumber(this->theTimeStampString, time_stamp, FABRIC_SERVER_TIME_STAMP_LENGTH_SIZE);
    this->debug(true, "setTimeStampString", this->timeStampString());
}

void DFabricClass::logit (char const *str0_val, char const *str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangLogit(s, str1_val);
}

void DFabricClass::abend (char const *str0_val, char const *str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangAbend(s, str1_val);
}
