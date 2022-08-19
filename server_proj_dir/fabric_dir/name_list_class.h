/*
  Copyrights reserved
  Written by Paul Hwang
  File name: name_list_class.h
*/

#pragma once

#include "../protocol_dir/web_fabric_protocol.h"
class FabricClass;

class NameListClass {
#define NAME_LIST_CLASS_NAME_LIST_TAG_SIZE WEB_FABRIC_PROTOCOL_NAME_LIST_TAG_SIZE
#define NAME_LIST_CLASS_MAX_NAME_LIST_TAG 999
#define NAME_LIST_CLASS_NAME_LIST_BUFFER_SIZE 10240

    char theObjectName[64];
    FabricClass *theFabricObject;
    int theNameListTag;
    char theNameList[NAME_LIST_CLASS_NAME_LIST_BUFFER_SIZE + 4];

    void debug(int on_off_val, char const* str0_val, char const* str1_val) {if (on_off_val) this->logit(str0_val, str1_val);};
    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);

public:
    NameListClass(FabricClass *fabric_object_val);
    ~NameListClass(void);
    char *objectName(void) {return this->theObjectName;}

    int nameListTag(void) {return this->theNameListTag;}

    void updateNameList(void);
    char *getNameList(int tag_val);
};
