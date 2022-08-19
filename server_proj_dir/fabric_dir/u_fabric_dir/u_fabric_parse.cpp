/*
  Copyrights reserved
  Written by Paul Hwang
  File name: d_fabric_export.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "../../protocol_dir/net_port_protocol.h"
#include "../../protocol_dir/fabric_theme_protocol.h"
#include "../../protocol_dir/web_fabric_protocol.h"
#include "../../protocol_dir/session_mgr_protocol.h"
#include "u_fabric_class.h"
#include "../fabric_class.h"
#include "../d_fabric_dir/d_fabric_class.h"
#include "../link_class.h"
#include "../session_class.h"
#include "../group_class.h"

void UFabricClass::exportedParseFunction(char *data_val)
{
    if (1) { /* debug */
        this->logit("exportedParseFunction", data_val);
    }

    if (*data_val == FABRIC_THEME_PROTOCOL_RESPOND_IS_SETUP_ROOM) {
        this->processSetupRoomResponse(data_val + 1);
        return;
    }

    if (*data_val == FABRIC_THEME_PROTOCOL_RESPOND_IS_PUT_ROOM_DATA) {
        this->processPutRoomDataResponse(data_val + 1);
        return;
    }

    this->abend("exportedParseFunction", data_val);
}

void UFabricClass::processSetupRoomResponse(char *data_val)
{
    this->debug(true, "processSetupRoomResponse", data_val);

    char *group_id_index_val = data_val;

    char *downlink_data;
    char *data_ptr;
	char *output_data;
    int session_array_size;

    GroupClass *group = this->theFabricObject->searchGroup(group_id_index_val);
    if (group) {
        group->setRoomIdIndex(group_id_index_val + GROUP_MGR_PROTOCOL_GROUP_ID_INDEX_SIZE);
        group->setSessionTableArray((SessionClass **) phwangArrayMgrGetArrayTable(group->sessionArrayMgr(), &session_array_size));
        printf("++++++++++++++++++++++++++++++++++++++++++++%d\n", session_array_size);
        for (int i = 0; i < session_array_size; i++) {
            SessionClass *session = group->sessionTableArray(0);
            session->linkObject()->setPendingSessionSetup3(session->sessionIdIndex(), "");
        }
    }
}

void UFabricClass::processPutRoomDataResponse(char *data_val)
{
    char *downlink_data;
    char *data_ptr;
    int session_array_size;

    this->debug(true, "processPutRoomDataResponse", data_val);

    GroupClass *group = this->theFabricObject->searchGroup(data_val);
    if (!group) {
        this->abend("processPutRoomDataResponse", "null group");
        return;
    }
    data_val += GROUP_MGR_PROTOCOL_GROUP_ID_INDEX_SIZE;

    group->setSessionTableArray((SessionClass **) phwangArrayMgrGetArrayTable(group->sessionArrayMgr(), &session_array_size));
    for (int i = 0; i < session_array_size; i++) {
        SessionClass *session = group->sessionTableArray(i);
        if (session) {
            session->enqueuePendingDownLinkData(data_val);
        }
    }
}
