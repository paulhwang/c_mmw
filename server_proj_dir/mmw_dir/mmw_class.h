/*
  Copyrights reserved
  Written by Paul Hwang
  File name: mmw_class.h
*/

#pragma once
#include <pthread.h>

#define MMW_CLASS_INPUT_QUEUE_SIZE 5000

class FabricClass;
class MmwInputClass;

class MmwClass {
    FabricClass *theFabricObject;
    MmwInputClass *theMmwInputObject;
    pthread_t theInputThread;
    void *theInputQueue;

    MmwInputClass *mmwInputObject(void) { return this->theMmwInputObject; }

    void startInputThread(void);

    void debug(int on_off_val, char const *str0_val, char const *str1_val) {if (on_off_val) this->logit(str0_val, str1_val);};
    void logit(char const *str0_val, char const *str1_val);
    void abend(char const *str0_val, char const *str1_val);

  public:
    void inputThreadFunction(void);
    char *readInputData(void);

    MmwClass(FabricClass *fabric_object_val);
    ~MmwClass(void);
    char const *objectName(void) {return "MmwClass";}
};
