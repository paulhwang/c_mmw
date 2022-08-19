/*
  Copyrights reserved
  Written by Paul Hwang
  File name: name_list_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "name_list_class.h"
#include "fabric_class.h"
#include "link_class.h"
#include "../../phwang_dir/list_mgr_dir/list_mgr_class.h"

NameListClass::NameListClass (FabricClass *fabric_object_val)
{
    memset(this, 0, sizeof(*this));
    this->theFabricObject = fabric_object_val;
    this->theNameListTag = 0;
    strcpy(this->theObjectName, "NameListClass");

    this->debug(true, "NameListClass", "init");
}

NameListClass::~NameListClass (void)
{
    if (strcmp(this->objectName(), "NameListClass")) {
        this->abend("~NameListClass", this->objectName());
    }
    strcpy(this->theObjectName, "NameListClassDummy");
}

void NameListClass::updateNameList (void)
{
    void *link_list_mgr = this->theFabricObject->linkListMgrObject();

    int max_index = phwnagListMgrGetMaxIndex(link_list_mgr, "NameListClass::updateNameList()");
    LinkClass **link_entry_array = (LinkClass **) phwangListMgrGetEntryTableArray(link_list_mgr);
    char *ptr = this->theNameList;
    int name_len;
    int name_list_size = NAME_LIST_CLASS_NAME_LIST_TAG_SIZE;

    this->theNameListTag++;
    if (this->theNameListTag > NAME_LIST_CLASS_MAX_NAME_LIST_TAG) {
        this->theNameListTag = 1;
    }

    for (int i = max_index; i >= 0; i--) {
        if (link_entry_array[i]) {
            if (ptr == this->theNameList) {
                phwangEncodeNumber(ptr, this->theNameListTag, NAME_LIST_CLASS_NAME_LIST_TAG_SIZE);
                ptr += NAME_LIST_CLASS_NAME_LIST_TAG_SIZE;
            }
            else {
                *ptr++ = ',';
            }
            *ptr++ = '"';
            name_len = strlen(link_entry_array[i]->linkName());
            memcpy(ptr, link_entry_array[i]->linkName(), name_len);
            ptr += name_len;
            *ptr++ = '"';
            name_list_size += (name_len + 3);
        }
    }
    *ptr = 0;

    if (name_list_size > NAME_LIST_CLASS_NAME_LIST_BUFFER_SIZE) {
        printf("name_list_size=%d\n", name_list_size);
        this->abend("updateNameList", "buffer too small");
    }

    this->debug(true, "updateNameList", this->theNameList);
}

char *NameListClass::getNameList(int tag_val)
{
	if (this->theNameListTag == tag_val) {
		return 0;
	}
	return this->theNameList;
}

void NameListClass::logit (char const *str0_val, char const *str1_val) {
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangLogit(s, str1_val);
}

void NameListClass::abend (char const *str0_val, char const *str1_val) {
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangAbend(s, str1_val);
}
