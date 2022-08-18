/*
  Copyrights reserved
  Written by Paul Hwang
  File name: server_main.cpp
*/

#include <unistd.h>
#include "../../phwang_dir/phwang.h"
//#include "../protocol_dir/net_port_protocol.h"
#include "server_root_class.h"

int main (int arc, char **argv) {
    ServerRootClass *serverRootObject = new ServerRootClass();

    sleep(10);

    int register_tag;
    //phwangRegisterProgramProcess(&register_tag, argv[0], HTTP_FABRIC_PROTOCOL_TRANSPORT_PORT_NUMBER);
}

