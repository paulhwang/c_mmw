/*
  Copyrights reserved
  Written by Paul Hwang
  File name: queue_class.h
*/

#pragma once

#include <pthread.h>
class QueueEntryClass;
class SuspendClass;

class QueueClass
{
#define QUEUE_CLASS_DEFAULT_MAX_QUEUE_SIZE 256
    SuspendClass *theSuspendObject;
    int theQueueSize;
    QueueEntryClass *theQueueHead;
    QueueEntryClass *theQueueTail;
    int theMaxQueueSize;
    pthread_mutex_t theMutex;

    void enqueueEntry(QueueEntryClass *entry);
    QueueEntryClass *dequeueEntry(void);
    int queueSize(void) {return this->theQueueSize;}

    void abendQueue(char const *msg_val);
    void flushQueue(void);

    void debug(int on_off_val, char const *str0_val, char const *str1_val) {if (on_off_val) this->logit(str0_val, str1_val);};
    void logit(char const *str0_val, char const *str1_val);
    void abend(char const *str0_val, char const *str1_val);

public:
    QueueClass(int do_suspend_val, int max_size_val);
    ~QueueClass(void);
    char const *objectName(void) {return "QueueClass";}
    
    void enqueueData(void *data_val);
    void *dequeueData(void);
};
