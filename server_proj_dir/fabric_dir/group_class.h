/*
  Copyrights reserved
  Written by Paul Hwang
  File name: group_class.h
*/

#pragma once
#include "../../phwang_dir/list_mgr_dir/list_entry_class.h"
#include "../protocol_dir/group_mgr_protocol.h"
#include "../protocol_dir/room_mgr_protocol.h"
#include "../protocol_dir/session_mgr_protocol.h"

class SessionClass;
class FabricClass;

class GroupClass : public ListEntryClass {
#define GROUP_CLASS_SESSION_ARRAY_SIZE 32
    FabricClass *theFabricObject;
    char theRoomIdIndex[ROOM_MGR_PROTOCOL_ROOM_ID_INDEX_SIZE + 4];
    void *theSessionArrayMgr;
    SessionClass **theSessionTableArray;

    void debug(int on_off_val, char const *str0_val, char const *str1_val) {if (on_off_val) this->logit(str0_val, str1_val);};
    void logit(char const *str0_val, char const *str1_val);
    void abend(char const *str0_val, char const *str1_val);

public:
    GroupClass(void *list_mgr_object_val, FabricClass *fabric_object_val, char *theme_data_val);
    ~GroupClass(void);
    char const* objectName(void) {return "GroupClass";}

    char *groupIdIndex(void) {return this->entryIdIndex();}
    char *roomIdIndex(void) {return this->theRoomIdIndex;}
    void *sessionArrayMgr(void) {return this->theSessionArrayMgr;}
    SessionClass *sessionTableArray(int index_val) {return this->theSessionTableArray[index_val];}
    void setSessionTableArray(SessionClass **val) {this->theSessionTableArray = val;}

    void setRoomIdIndex(char *val) {memcpy(this->theRoomIdIndex, val, ROOM_MGR_PROTOCOL_ROOM_ID_INDEX_SIZE);}
    void insertSession(SessionClass *session_object_val) {phwangArrayMgrInsertElement(this->theSessionArrayMgr, session_object_val);}
    void removeSession(SessionClass *session_object_val) {phwangArrayMgrRemoveElement(this->theSessionArrayMgr, session_object_val);}
};
