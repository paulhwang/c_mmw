/*
  Copyrights reserved
  Written by Paul Hwang
  File name: session_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "session_class.h"

SessionClass::SessionClass (void *list_mgr_object_val, LinkClass *link_object_val):
        ListEntryClass(list_mgr_object_val),
        theLinkObject(link_object_val),
        theGroupObject(0)
{
    this->thePendingDownLinkDataQueue = phwangMallocQueue(0);

    this->debug(true, "SessionClass", this->sessionIdIndex());
}

SessionClass::~SessionClass (void)
{
    phwangFreeQueue(this->thePendingDownLinkDataQueue, "SessionClass::~SessionClass()");
}

void SessionClass::enqueuePendingDownLinkData(char *data_val)
{
    char *buf = (char *) malloc(strlen(data_val) + 4);
    strcpy(buf, data_val);
    phwangEnqueue(this->thePendingDownLinkDataQueue, buf);
}

void SessionClass::logit (char const* str0_val, char const* str1_val) {
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangLogit(s, str1_val);
}

void SessionClass::abend (char const* str0_val, char const* str1_val) {
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangAbend(s, str1_val);
}
