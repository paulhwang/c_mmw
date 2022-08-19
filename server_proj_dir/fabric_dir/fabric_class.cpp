/*
  Copyrights reserved
  Written by Paul Hwang
  File name: fabric_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "../../phwang_dir/list_mgr_dir/list_mgr_class.h"
#include "fabric_class.h"
#include "u_fabric_dir/u_fabric_class.h"
#include "d_fabric_dir/d_fabric_class.h"
#include "group_class.h"
#include "link_class.h"
#include "name_list_class.h"

FabricClass::FabricClass (void)
{
    memset(this, 0, sizeof(*this));
    this->theUFabricObject = new UFabricClass(this);
    this->theDFabricObject = new DFabricClass(this);
    this->theNameListObject = new NameListClass(this);
    this->theLinkListMgrObject = phwangListMgrMalloc("LINK", LINK_MGR_PROTOCOL_LINK_ID_SIZE, LINK_MGR_PROTOCOL_LINK_INDEX_SIZE, 100);
    this->theGroupListMgrObject = phwangListMgrMalloc("GROUP", GROUP_MGR_PROTOCOL_GROUP_ID_SIZE, GROUP_MGR_PROTOCOL_GROUP_INDEX_SIZE, 500);
    this->startWatchDogThread();

    this->debug(true, "FabricClass", "init");
}

FabricClass::~FabricClass (void)
{
    this->theDFabricObject->~DFabricClass(); 
    this->theUFabricObject->~UFabricClass(); 
    this->theNameListObject->~NameListClass();
    this->debug(true, "~FabricClass", "exit");
}

void FabricClass::linkKeepAliveExamine (void)
{
    if (1) {
        return;
    }
    
    int max_index = phwnagListMgrGetMaxIndex(this->theLinkListMgrObject, "FabricClass::linkKeepAliveExamine()");
    LinkClass **link_entry_array = (LinkClass **) phwangListMgrGetEntryTableArray(this->theLinkListMgrObject);

    for (int i = max_index ; i >= 0; i--) {
        LinkClass *link = link_entry_array[i];
        if (link && link->keepAliveTime() && link->keepAliveTimerExpired()) {
            if (1) { /* debug */
                char s[128];
                sprintf(s, "(***link expired***) linkName=%s linkIdIndex=%s", link->linkName(), link->linkIdIndex());
                this->logit("linkKeepAliveExamine", s);
            }
            phwangListMgrRemoveEntry(this->theLinkListMgrObject, link);
            delete link;
        }
    }

}

LinkClass *FabricClass::mallocLink (char const *data_val)
{
    this->debug(true, "mallocLink", data_val);

    if (strcmp(((ListMgrClass *) this->linkListMgrObject())->objectName(), "ListMgrClass")) {
        this->abend("mallocLink", "bad name 000");
    }


    LinkClass *link = new LinkClass(this->theLinkListMgrObject, this, data_val);

    if (strcmp(((ListMgrClass *) this->linkListMgrObject())->objectName(), "ListMgrClass")) {
        this->abend("mallocLink", "bad name 111");
    }

    this->theNameListObject->updateNameList();
    return link;
}

void FabricClass::freeLink (LinkClass *link_object_val)
{
    this->debug(true, "freeLink", link_object_val->linkIdIndex());
    if (!link_object_val) {
        return;
    }

    if (strcmp(((ListMgrClass *) this->linkListMgrObject())->objectName(), "ListMgrClass")) {
        this->abend("freeLink", "bad name 000");
    }

    link_object_val->~LinkClass();

    if (strcmp(((ListMgrClass *) this->linkListMgrObject())->objectName(), "ListMgrClass")) {
        this->abend("freeLink", "bad name 111");
    }

    this->theNameListObject->updateNameList();
}

LinkClass *FabricClass::searchLinkByName (char *name_val)
{
    int max_index = phwnagListMgrGetMaxIndex(this->theLinkListMgrObject, "FabricClass::searchLinkByName()");
    LinkClass **link_entry_array = (LinkClass **) phwangListMgrGetEntryTableArray(this->theLinkListMgrObject);

    for (int i = max_index ; i >= 0; i--) {
        if (link_entry_array[i]) {
            if (!strcmp(link_entry_array[i]->linkName(), name_val)) {
                return link_entry_array[i];
            }
        }
    }
    return 0;
}

GroupClass *FabricClass::mallocGroup (char *theme_data_val)
{
    this->debug(true, "mallocGroup", "");
    GroupClass *group = new GroupClass(this->theGroupListMgrObject, this, theme_data_val);
    return group;
}

SessionClass *FabricClass::serachLinkAndSession (char *data_val)
{
    LinkClass *link = this->searchLink(data_val, 0);
    if (!link) {
        this->abend("serachLinkAndSession", "null link");
        return 0;
    }

    return link->searchSession(data_val + LINK_MGR_PROTOCOL_LINK_ID_INDEX_SIZE);
}

void FabricClass::logit (char const *str0_val, char const *str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangLogit(s, str1_val);
}

void FabricClass::abend (char const *str0_val, char const *str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangAbend(s, str1_val);
}
