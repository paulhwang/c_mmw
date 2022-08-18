/*
  Copyrights reserved
  Written by Paul Hwang
  File name: suspend_class.h
*/

#pragma once

#include <pthread.h>

class SuspendClass
{
    pthread_mutex_t *mutex;
    pthread_cond_t *cond;

public:
    SuspendClass(void);
    ~SuspendClass(void);

    void wait(void);
    void signal(void);
};
