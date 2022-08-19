/*
  Copyrights reserved
  Written by Paul Hwang
  File name: group_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "../../phwang_dir/list_mgr_dir/list_mgr_class.h"
#include "group_class.h"
#include "fabric_class.h"

GroupClass::GroupClass (void *list_mgr_object_val, FabricClass *fabric_object_val, char *theme_data_val):
        ListEntryClass(list_mgr_object_val),
        theFabricObject(fabric_object_val)
{
    this->theSessionArrayMgr = phwangArrayMgrMalloc(this->objectName(), 'o', 10);
    this->theSessionTableArray = 0;

    this->debug(true, "GroupClass", this->groupIdIndex());
}

GroupClass::~GroupClass (void)
{
    phwangArrayMgrFree(this->theSessionArrayMgr);
}

void GroupClass::logit (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangLogit(s, str1_val);
}

void GroupClass::abend (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangAbend(s, str1_val);
}
