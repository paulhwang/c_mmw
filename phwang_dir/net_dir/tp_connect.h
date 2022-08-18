/*
  Copyrights reserved
  Written by Paul Hwang
  File name: tp_connect.h
*/

void *globalTpConnect (
                    unsigned long ip_addr_val, 
                    unsigned short port_val, 
                    void (*receive_callback_val)(void *, void *, void *), 
                    void *receive_object_val,
                    char const *who_val);
