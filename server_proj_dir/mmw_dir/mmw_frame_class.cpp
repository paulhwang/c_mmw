/*
  Copyrights reserved
  Written by Paul Hwang
  File name: mmw_frame_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "mmw_frame_class.h"

MmwFrameClass::MmwFrameClass (void)
{
    this->debug(false, "MmwFrameClass", "start");

    this->theArraySize = 0;
    this->theLineArray = (char **) malloc(sizeof(char *) * this->theMaxArraySize);
    memset(this->theLineArray, 0, sizeof(char *) * this->theMaxArraySize);
}

MmwFrameClass::~MmwFrameClass (void)
{
    this->debug(false, "~MmwFrameClass", "start");
    for (int i = 0; i < this->theArraySize; i++) {
        if (this->theLineArray[i]) {
            free(this->theLineArray[i]);
            this->theLineArray[i] = 0;
        }
    }
    free(this->theLineArray);
}

void MmwFrameClass::parseFrame (void)
{
    if (memcmp(this->theLineArray[0], "frameNum", 7) != 0) {
        this->porcessHeaderFrame();
    }
    else {
        this->porcessNormalFrame();
    }
}


void MmwFrameClass::porcessHeaderFrame (void)
{
    this->theFrameType = MMW_FRAME_CLASS_TYPE_HEADER;
}

void MmwFrameClass::porcessNormalFrame (void)
{
    this->theFrameType = MMW_FRAME_CLASS_TYPE_NORMAL;

}

void MmwFrameClass::logit (char const *str0_val, char const *str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangLogit(s, str1_val);
}

void MmwFrameClass::abend (char const *str0_val, char const *str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    //phwangAbend(s, str1_val);
}
