/*
  Copyrights reserved
  Written by Paul Hwang
  File name: d_fabric_transmit.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "../../protocol_dir/web_fabric_protocol.h"
#include "d_fabric_class.h"

void DFabricClass::transmitFunction (void *tp_transfer_object_val, char *data_val)
{
  if (*data_val != WEB_FABRIC_PROTOCOL_RESPOND_IS_GET_LINK_DATA) {
      this->debug(true, "transmitFunction", data_val);
    }

    phwangTpTransmit(tp_transfer_object_val, data_val);
}
