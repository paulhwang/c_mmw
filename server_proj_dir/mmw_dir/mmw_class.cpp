/*
  Copyrights reserved
  Written by Paul Hwang
  File name: mmw_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "mmw_class.h"
#include "mmw_input_class.h"
#include "../server_dir/server_root_class.h"

MmwClass::MmwClass (ServerRootClass *server_root_object_val)
{
    this->debug(true, "MmwClass", "start");
    
    memset(this, 0, sizeof(*this));
    this->theServerRootObject = server_root_object_val;

    this->theInputQueue = phwangMallocSuspendedQueue(MMW_CLASS_INPUT_QUEUE_SIZE);

    this->theMmwInputObject = new MmwInputClass(this);
    this->startInputThread();
}

MmwClass::~MmwClass (void)
{
    this->debug(true, "~MmwClass", "exit");
}

char *MmwClass::readInputData (void)
{
    char *data = (char *) phwangDequeue(this->theInputQueue, "MmwClass");
    if (data) {
        this->debug(false, "readInputData", "data");
    }

    return data;
}

void MmwClass::logit (char const *str0_val, char const *str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangLogit(s, str1_val);
}

void MmwClass::abend (char const *str0_val, char const *str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    //phwangAbend(s, str1_val);
}
