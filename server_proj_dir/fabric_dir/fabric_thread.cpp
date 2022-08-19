/*
  Copyrights reserved
  Written by Paul Hwang
  File name: fabric_thread.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "fabric_class.h"

void *FabricClassWatchDogThreadFunction (void *fabric_object_val)
{
    ((FabricClass *) fabric_object_val)->watchDogThreadFunction();
}

void FabricClass::startWatchDogThread (void)
{
    this->debug(false, "startWatchDogThread", "");

    int r = pthread_create(&this->theWatchDogThread, 0, FabricClassWatchDogThreadFunction, this);
    if (r) {
        this->logit("startWatchDogThread", "fail");
        return;
    }
}

void FabricClass::watchDogThreadFunction (void)
{
    this->debug(false, "watchDogThreadFunction", "");
    while (1) {
        this->linkKeepAliveExamine();
        sleep(1);
    }
}
