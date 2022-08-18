/*
  Copyrights reserved
  Written by Paul Hwang
  File name: list_entry_class.h
*/

#pragma once

class ListMgrClass;

class ListEntryClass {
#define LIST_ENTRY_CLASS_ID_INDEX_BUFFER_SIZE 32
    ListMgrClass *theListMgrObject;
    int theEntryId;
    int theEntryIndex;
    char theEntryIdIndex[LIST_ENTRY_CLASS_ID_INDEX_BUFFER_SIZE];

    void debug(int on_off_val, char const *str0_val, char const *str1_val) {if (on_off_val) this->logit(str0_val, str1_val);};
    void logit(char const *str0_val, char const *str1_val);
    void abend(char const *str0_val, char const *str1_val);

public:
    ListEntryClass(void *list_mgr_object);
    ~ListEntryClass(void);
    char const* objectName(void) {return "ListEntryClass";}

    int entryId(void) {return this->theEntryId;}
    void setEntryId(int val) {this->theEntryId = val;}
    int entryIndex(void) {return this->theEntryIndex;}
    void setEntryIndex(int val) {this->theEntryIndex = val;}
    char *entryIdIndex(void) {return this->theEntryIdIndex;}
};
