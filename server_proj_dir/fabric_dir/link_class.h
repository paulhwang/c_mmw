/*
  Copyrights reserved
  Written by Paul Hwang
  File name: link_class.h
*/

#pragma once
#include <time.h>
#include "../../phwang_dir/list_mgr_dir/list_entry_class.h"
#include "../protocol_dir/link_mgr_protocol.h"

class SessionClass;
class FabricClass;

class LinkClass : public ListEntryClass {
#define LINK_CLASS_LINK_NAME_BUF_SIZE 32
#define LINK_CLASS_KEEP_ALIVE_TIMEOUT 60
private:
    FabricClass *theFabricObject;
    char theLinkName[LINK_CLASS_LINK_NAME_BUF_SIZE + 4];
    void *theSessionListMgrObject;
    void *thePendingSessionSetupQueue;
    void *thePendingSessionSetupQueue3;
    char theNameListChanged;
    time_t theKeepAliveTime;

    void debug(int on_off_val, char const *str0_val, char const *str1_val) {if (on_off_val) this->logit(str0_val, str1_val);};
    void logit(char const *str0_val, char const *str1_val);
    void abend(char const *str0_val, char const *str1_val);

public:
    LinkClass(void *list_mgr_object_val, FabricClass *fabric_object_val, char const* link_name_val);
    ~LinkClass(void);
    char const *objectName(void) {return "LinkClass";}

    char *linkName(void) {return this->theLinkName;}
    char *linkIdIndex(void) {return this->entryIdIndex();}
    time_t keepAliveTime(void) {return this->theKeepAliveTime;}

    SessionClass *mallocSession(void);
    void *sessionListMgrObject(void) {return this->theSessionListMgrObject;}
    SessionClass *searchSession(char *data_val) {return (SessionClass *) phwangListMgrSearchEntry(this->theSessionListMgrObject, data_val, 0);}
    char *getPendingSessionSetup(void) {return (char *) phwangDequeue(this->thePendingSessionSetupQueue, "LinkClass::getPendingSessionSetup()");}
    char *getPendingSessionSetup3(void) {return (char *) phwangDequeue(this->thePendingSessionSetupQueue3, "LinkClass::getPendingSessionSetup3()");}
    void setPendingSessionSetup(char *session_id_index_val, char *topic_data_val);
    void setPendingSessionSetup3(char *session_id_index_val, char *topic_data_val);
    void resetKeepAliveTime(void) {this->theKeepAliveTime = time((time_t *) 0);}
    int keepAliveTimerExpired(void) {return (time((time_t *) 0) - this->theKeepAliveTime) > LINK_CLASS_KEEP_ALIVE_TIMEOUT;}
};
