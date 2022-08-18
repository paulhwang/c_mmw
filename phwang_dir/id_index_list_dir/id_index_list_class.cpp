/*
  Copyrights reserved
  Written by Paul Hwang
  File name: id_index_list_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "id_index_list_class.h"

IdIndexListClass::IdIndexListClass (void *caller_object_val, int id_size_val, int index_size_val)
{
    memset(this, 0, sizeof(IdIndexListClass));
    this->theCallerObject = caller_object_val;
    this->theIdSize = id_size_val;
    this->theIndexSize = index_size_val;
    this->theIdIndexSize = this->theIdSize + this->theIndexSize;

    this->theGlobalEntryId = 0;
    this->theMaxIdIndexTableIndex = 0;

    this->debug(true, "IdIndexListClass", "init");
}

IdIndexListClass::~IdIndexListClass (void)
{
}

void IdIndexListClass::insertIdIndex (char *id_index_val)
{
    char *buf = (char *) malloc(this->theIdIndexSize + 4);
    memcpy(buf, id_index_val, this->theIdIndexSize);
    buf[this->theIdIndexSize] = 0;

    int i = 0;
    while (i < this->theMaxIdIndexTableIndex) {
        if (!this->theIdIndexTableArray[i]) {
            this->theIdIndexTableArray[i] = buf;
            return;
        }
        i++;
    }

    if (this->theMaxIdIndexTableIndex < LIST_MGR_ID_INDEX_ARRAY_SIZE) {
        this->theIdIndexTableArray[this->theMaxIdIndexTableIndex] = buf;
        this->theMaxIdIndexTableIndex++;
        return;
    }

    free(buf);
    this->abend("insertIdIndex", "theIdIndexTableArray is full");
}

void IdIndexListClass::removeIdIndex (char *id_index_val)
{
    int i = 0;
    while (i < this->theMaxIdIndexTableIndex) {
        if (!memcmp(this->theIdIndexTableArray[i], id_index_val, this->theIdIndexSize)) {
            free(this->theIdIndexTableArray[i]);
            this->theIdIndexTableArray[i] = 0;
            return;
        }
        i++;
    }
    this->abend("removeIdIndex", "not found");
}

void IdIndexListClass::logit (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangLogit(s, str1_val);
}

void IdIndexListClass::abend (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangAbend(s, str1_val);
}
