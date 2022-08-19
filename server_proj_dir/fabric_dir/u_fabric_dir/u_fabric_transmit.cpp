/*
  Copyrights reserved
  Written by Paul Hwang
  File name: u_fabric_transmit.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "u_fabric_class.h"

void UFabricClass::transmitFunction (char *data_val)
{
    this->logit("transmitFunction", data_val);

    if (!this->theTpTransferObject) {
        this->abend("transmitFunction", "null theTpTransferObject");
        return;
    }

    phwangTpTransmit(this->theTpTransferObject, data_val);
}
