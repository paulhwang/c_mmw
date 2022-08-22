/*
  Copyrights reserved
  Written by Paul Hwang
  File name: mmw_thread.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "mmw_class.h"
#include "mmw_input_class.h"

void *MmwClassInputThreadFunction (void *fabric_object_val)
{
    ((MmwClass *) fabric_object_val)->inputThreadFunction();
}

void MmwClass::startInputThread (void)
{
    this->debug(false, "startInputThread", "");

    int r = pthread_create(&this->theInputThread, 0, MmwClassInputThreadFunction, this);
    if (r) {
        this->logit("startInputThread", "fail");
        return;
    }
}

void MmwClass::inputThreadFunction (void)
{
    this->debug(false, "inputThreadFunction", "");

    int open_result = this->mmwInputObject()->openFile("data/walking_around.txt", "r");
    if (open_result == -1) {
        this->logit("openFile", "cannot open file");
        return;
    }

    this->mmwInputObject()->readIdleData();
    
    while (1) {
        this->mmwInputObject()->readInput();
        return;
    }
}
