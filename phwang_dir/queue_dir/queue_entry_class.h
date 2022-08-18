/*
  Copyrights reserved
  Written by Paul Hwang
  File name:queue_entry_class.h
*/

#pragma once

class QueueEntryClass
{
    friend class QueueClass;

    char theObjectName[64];
    QueueEntryClass *next;
    QueueEntryClass *prev;
    void *data;

    void deleteQueueEntry(void);

    void debug(int on_off_val, char const *str0_val, char const *str1_val) {if (on_off_val) this->logit(str0_val, str1_val);};
    void logit(char const *str0_val, char const *str1_val);
    void abend(char const *str0_val, char const *str1_val);

public:
    QueueEntryClass(void);
    ~QueueEntryClass(void);
    char *objectName(void) {return this->theObjectName;}
};
