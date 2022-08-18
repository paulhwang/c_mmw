/*
  Copyrights reserved
  Written by Paul Hwang
  File name: phwang_class.h
*/

#pragma once

#define LOGIT_BUF_SIZE 512

class PhwangClass {
    void debug(int on_off_val, char const *str0_val, char const *str1_val) {if (on_off_val) this->logit(str0_val, str1_val);};
    void logit(char const *str0_val, char const *str1_val);
    void logit3(char const *str0_val, char const *str1_val, char const *str2_val);
    void abend(char const *str0_val, char const *str1_val);
    void abend3(char const *str0_val, char const *str1_val, char const *str2_val);

public:
    PhwangClass(void){}
    ~PhwangClass(void){}
    char const *objectName(void) {return "PhwangClasss";}

    /* logit */
    void phwangDebug(int on_off_val, char const *str0_val, char const *str1_val) {if (on_off_val) this->phwangLogit(str0_val, str1_val);}
    void phwangLogit(char const *str0_val, char const *str1_val);
    void phwangLogit3(char const *str0_val, char const *str1_val, char const *str2_val);
    void phwangAbend(char const *str0_val, char const *str1_val);
    void phwangAbend3(char const *str0_val, char const *str1_val, char const *str2_val);
    void printBoard(char const *data_val, int board_size_val);

    /* malloc and free */
    void *phwangMalloc(int size_val, char const *who_val);
    void phwangFree(void *data_val, char const *who_val);

    /* encode */
    void encodeNumber(char *str_val, int number_val, int size_val);
    int decodeNumber(char const *str_val, int size_val);
    void encodeIdIndex(char *str_val, int id_val, int id_size_val, int index_val, int index_size_val);
    void decodeIdIndex(char const *str_val, int *id_ptr_val, int id_size_val, int *index_ptr_val, int index_size_val);

    /* queue */
    void *mallocQueue(int do_suspend_val, int max_size_val);
    void freeQueue(void *queue_val);
    void enqueue(void *queue_val, void *data_val);
    void *dequeue(void *queue_val);

    /* list_mgr */
    void *listMgrMalloc(char const *caller_name_val, int id_size_val, int index_size_val, int global_entry_id_val);
    void  listMgrFree(void *list_mgr_val);
    void  listMgrRemoveEntry(void *list_mgr_val, void *entry_val);
    void *listMgrSearchEntry(void *list_mgr_val, char const *data_val, void *extra_data_val);
    int   listMgrGetMaxIndex(void *list_mgr_val, char const *who_val);
    void *listMgrGetEntryTableArray(void *list_mgr_val);

    /* array_mgr */
    void *arrayMgrMalloc(char const *caller_name_val, char array_type_val, int max_array_size_val);
    void  arrayMgrFree(void *array_mgr_val);
    void  arrayMgrInsertElement(void *array_mgr_val, void *element_val);
    void  arrayMgrRemoveElement(void *array_mgr_val, void *element_val);
    void *arrayMgrGetArrayTable(void *array_mgr_val, int *array_size_ptr);

    /* tp */
    void *mallocTpServer (
            void *caller_object_val,
            unsigned short port_val,
            void (*accept_callback_func_val)(void *, void *),
            void *accept_callback_parameter_val,
            void (*receive_callback_func_val)(void *, void *, void *),
            void *receive_callback_parameter_val,
            char const *who_val);
    void *tpConnect(
            unsigned long ip_addr_val, 
            unsigned short port_val, 
            void (*receive_callback_val)(void *, void *, void *), 
            void *receive_object_val,
            char const *who_val);
    void freeTpServer(void *tp_server_object_val);
    void freeTpTransfer(void *tp_transfer_object_val);
    void tpTransmit(void *tp_transfer_object_val, char *data_val);

    /* db */
    void createDbDb(char *db_val);
    void createDbTable(char *table_val);

    /* register */
    void registerProgramProcess(int *register_tag_ptr_val, char *program_name_val, unsigned short port_val);
};
