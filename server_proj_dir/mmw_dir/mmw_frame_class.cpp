/*
  Copyrights reserved
  Written by Paul Hwang
  File name: mmw_frame_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "mmw_frame_class.h"

MmwFrameClass::MmwFrameClass (void)
{
    this->debug(true, "MmwFrameClass", "start");

    this->theArraySize = 0;
    this->theLineArray = (char **) malloc(8 * 200);
}

MmwFrameClass::~MmwFrameClass (void)
{
    this->debug(true, "~MmwFrameClass", "exit");
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
