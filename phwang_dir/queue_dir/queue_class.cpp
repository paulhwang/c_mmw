/*
  Copyrights reserved
  Written by Paul Hwang
  File name: queue_class.cpp
*/

#include <string.h>
#include <stdlib.h>
#include "../phwang.h"
#include "queue_class.h"
#include "queue_entry_class.h"
#include "../suspend_dir/suspend_class.h"

QueueClass::QueueClass(int do_suspend_val, int max_size_val)
{
    memset(this, 0, sizeof (*this));
    this->theMaxQueueSize = max_size_val;

    if (do_suspend_val) {
        this->theSuspendObject = new SuspendClass();
    }
    else {
        this->theSuspendObject = 0;
    }

    if (!this->theMaxQueueSize) {
        this->theMaxQueueSize = QUEUE_CLASS_DEFAULT_MAX_QUEUE_SIZE;
    }

    if (pthread_mutex_init(&this->theMutex, NULL) != 0) {
        this->abend("QueueClass", "pthread_mutex_init fail");
    }
}

QueueClass::~QueueClass(void)
{
    delete this->theSuspendObject;
}

void QueueClass::enqueueData (void *data_val)
{
    this->debug(false, "enqueueData", (char *) data_val);

    /* queue is too big */
    if (this->theMaxQueueSize && (this->theQueueSize > this->theMaxQueueSize)) {
        phwangFree(data_val, "QueueClass::enqueueData");
        this->abend("enqueueData", "queue full");
        return;
    }

    QueueEntryClass *entry = new QueueEntryClass();
    if (!entry) {
        this->abend("enqueueData", "fail to create new QueueEntryClass");
        return;
    }
    entry->data = data_val;

    this->abendQueue("enqueueData begin");
    pthread_mutex_lock(&this->theMutex);
    this->enqueueEntry(entry);
    pthread_mutex_unlock(&this->theMutex);
    this->abendQueue("enqueueData end");

    if (this->theSuspendObject) {
        this->theSuspendObject->signal();
    }
}

void *QueueClass::dequeueData (void)
{
    while (1) {
        if (!this->theQueueHead) {
            if (!this->theSuspendObject) {
                return 0;
            }
            this->theSuspendObject->wait();
        }
        else {
            this->abendQueue("dequeueData begin");
            pthread_mutex_lock(&this->theMutex);
            QueueEntryClass *entry = this->dequeueEntry();
            pthread_mutex_unlock(&this->theMutex);
            this->abendQueue("dequeueData end");

            if (entry) {
                if (strcmp(entry->objectName(), "QueueEntryClass")) {
                    this->abend("dequeueData", "bad objectName");
                }
                void *data = entry->data;
                delete entry;

                this->debug(false, "dequeueData", (char *) data);
                return data;
            }
        }
    }
}

void QueueClass::enqueueEntry(QueueEntryClass *entry)
{
    if (!this->theQueueHead) {
        entry->next = 0;  
        entry->prev = 0;
        this->theQueueHead = entry;
        this->theQueueTail = entry;
        this->theQueueSize = 1; 
    }
    else {        
        entry->next = 0;  
        entry->prev = this->theQueueTail;
        this->theQueueTail->next = entry;
        this->theQueueTail = entry;
        this->theQueueSize++;
    }
}

QueueEntryClass *QueueClass::dequeueEntry(void)
{
    QueueEntryClass *entry;

    if (this->theQueueSize == 0) {
        this->abend("dequeueEntry", "theQueueSize == 0");
        return 0;
    }

    if (this->theQueueSize == 1) {
        entry = this->theQueueHead;
        this->theQueueHead = this->theQueueTail = 0;
        this->theQueueSize = 0;
        return entry;
    }

    entry = this->theQueueHead;
    this->theQueueHead = this->theQueueHead->next;
    this->theQueueHead->prev = 0;
    this->theQueueSize--;

    return entry;
}

void QueueClass::abendQueue (char const *msg_val)
{
    QueueEntryClass *entry;
    int length;
 
    if (!this) {
        this->abend("abendQueue", "null this");
        return;
    }
 
    if (this->theQueueSize == 0) {
        if (this->theQueueHead || this->theQueueTail) {
            this->abend("abendQueue", "theQueueSize == 0");
            return;
        }
    }
    else {
        if (!this->theQueueHead) {
            this->abend("abendQueue", "null theQueueHead");
            return;
        }
    }

    pthread_mutex_lock(&this->theMutex);
    length = 0;
    entry = this->theQueueHead;
    while (entry) {
        length++;
        entry = entry->next;
    }
 
    if (length != this->theQueueSize) {
        printf("%s length=%d %d\n", msg_val, length, this->theQueueSize);
        this->abend("abendQueue", "from head: bad length");
    }

    length = 0;
    entry = this->theQueueTail;
    while (entry) {
        length++;
        entry = entry->prev;
    }
 
    if (length != this->theQueueSize) {
        printf("%s length=%d %d\n", msg_val, length, this->theQueueSize);
        this->abend("abendQueue", "from tail: bad length");
    }

    pthread_mutex_unlock(&this->theMutex);
}

void QueueClass::flushQueue(void)
{
    QueueEntryClass *entry, *entry_next; 
 
    pthread_mutex_lock(&this->theMutex);
    entry = this->theQueueHead;
    while (entry) {
        entry_next = entry->next;
        phwangFree(entry->data, "QueueClass::flushQueue");
        delete entry;
        this->theQueueSize--;
        entry = entry_next;
    }
    this->theQueueHead = this->theQueueTail = 0;
 
    if (this->theQueueSize) {
        this->abend("flushQueue", "theQueueSize");
    }

    pthread_mutex_unlock(&this->theMutex);
}

void QueueClass::logit (char const* str0_val, char const* str1_val)
{
    phwangLogit(str0_val, str1_val);
}

void QueueClass::abend (char const* str0_val, char const* str1_val)
{
    phwangAbend(str0_val, str1_val);
}
