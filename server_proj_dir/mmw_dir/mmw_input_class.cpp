/*
  Copyrights reserved
  Written by Paul Hwang
  File name: mmw_input_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "mmw_input_class.h"

MmwInputClass::MmwInputClass (MmwClass *mmw_object_val)
{
    this->debug(true, "MmwInputClass", "start");
    this->theMmwObject = mmw_object_val;
}

MmwInputClass::~MmwInputClass (void)
{
    this->debug(true, "~MmwInputClass", "exit");
}

void MmwInputClass::logit (char const *str0_val, char const *str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangLogit(s, str1_val);
}

void MmwInputClass::abend (char const *str0_val, char const *str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    //phwangAbend(s, str1_val);
}
