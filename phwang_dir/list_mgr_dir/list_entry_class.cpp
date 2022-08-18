/*
  Copyrights reserved
  Written by Paul Hwang
  File name: list_mgr_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "list_entry_class.h"
#include "list_mgr_class.h"

ListEntryClass::ListEntryClass (void *list_mgr_object)
{
    memset(this, 0, sizeof(*this));
    this->theListMgrObject = (ListMgrClass *) list_mgr_object;
    this->theEntryId = 0;
    this->theEntryIndex = 0;

    if (this->theListMgrObject->idSize() + this->theListMgrObject->indexSize() > LIST_ENTRY_CLASS_ID_INDEX_BUFFER_SIZE) {
        this->abend("ListEntryClass", "buffer too small");
    }

    this->theListMgrObject->insertEntry(this);
    phwangEncodeIdIndex(this->theEntryIdIndex, this->theEntryId, this->theListMgrObject->idSize(), this->theEntryIndex, this->theListMgrObject->indexSize());

    this->debug(true, "ListEntryClass", this->theEntryIdIndex);
}

ListEntryClass::~ListEntryClass (void)
{
}

void ListEntryClass::logit (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangLogit(s, str1_val);
}

void ListEntryClass::abend (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangAbend(s, str1_val);
}
