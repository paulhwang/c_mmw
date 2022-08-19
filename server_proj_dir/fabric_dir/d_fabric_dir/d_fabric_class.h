/*
  Copyrights reserved
  Written by Paul Hwang
  File name: d_server_class.h
*/

#pragma once

#include <pthread.h>
#include "../../protocol_dir/link_mgr_protocol.h"
#include "../fabric_class.h"

class FabricClass;

#define FABRIC_SERVER_TIME_STAMP_LENGTH_SIZE 8

class DFabricClass {
    FabricClass *theFabricObject;
    void *theTpServerObject;
    char theTimeStampString[FABRIC_SERVER_TIME_STAMP_LENGTH_SIZE + 16];

    void setTimeStampString(void);
    void startNetServer(void);
    void processSetupLink(void *tp_transfer_object_val, char *data_val);
    void processFreeLink(void *tp_transfer_object_val, char *data_val);
    void processGetLinkData(void *tp_transfer_object_val, char *data_val);
    void processGetNameList(void *tp_transfer_object_val, char *data_val);
    void processSetupSession(void *tp_transfer_object_val, char *data_val);
    void processSetupSession2(void *tp_transfer_object_val, char *data_val);
    void processSetupSession3(void *tp_transfer_object_val, char *data_val);
    void processFreeSession(void *tp_transfer_object_val, char *data_val);
    void processPutSessionData(void *tp_transfer_object_val, char *data_val);
    void processGetSessionData(void *tp_transfer_object_val, char *data_val);
    void errorProcessSetupLink(void *tp_transfer_object_val, char const *ajax_id_val, char const *err_msg_val);
    void errorProcessFreeLink(void *tp_transfer_object_val, char const *ajax_id_val, char const *err_msg_val);
    void errorProcessGetLinkData(void *tp_transfer_object_val, char const *ajax_id_val, char const *err_msg_val);
    void errorProcessGetNameList(void *tp_transfer_object_val, char const *ajax_id_val, char const *err_msg_val);
    void errorProcessSetupSession(void *tp_transfer_object_val, char const *ajax_id_val, char const *err_msg_val);
    void errorProcessSetupSession2(void *tp_transfer_object_val, char const *ajax_id_val, char const *err_msg_val);
    void errorProcessFreeSession(void *tp_transfer_object_val, char const *ajax_id_val, char const *err_msg_val);
    void errorProcessPutSessionData(void *tp_transfer_object_val, char const *ajax_id_val, char const *err_msg_val);
    void errorProcessGetSessionData(void *tp_transfer_object_val, char const *ajax_id_val, char const *err_msg_val);
    void mallocRoom(GroupClass *group_val, char *theme_info_val);

    char *timeStampString(void) {return this->theTimeStampString;}
    void debug(int on_off_val, char const *str0_val, char const *str1_val) {if (on_off_val) this->logit(str0_val, str1_val);}
    void logit(char const *str0_val, char const *str1_val);
    void abend(char const *str0_val, char const *str1_val);
   
public:
    DFabricClass(FabricClass *fabric_object_val);
    ~DFabricClass(void);
    char const *objectName(void) {return "DFabricClass";}

    void transmitFunction(void *tp_transfer_object_val, char *data_val);

    /* exports */
    void exportedNetAcceptFunction(void *tp_transfer_object_val);
    void exportedParseFunction(void *tp_transfer_object_val, char *data_val);
};
