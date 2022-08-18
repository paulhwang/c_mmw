/*
  Copyrights reserved
  Written by Paul Hwang
  File name: phwang_class.cpp
*/

#include <sys/socket.h>
#include <arpa/inet.h>
#include "phwang.h"
#include "phwang_class.h"
#include "queue_dir/queue_class.h"
#include "list_mgr_dir/list_mgr_class.h"
#include "array_mgr_dir/array_mgr_class.h"
#include "net_dir/tp_server_class.h"
#include "net_dir/tp_transfer_class.h"
#include "net_dir/tp_connect.h"
//#include "db_dir/db_postgre.h"

void PhwangClass::phwangLogit (char const *str0_val, char const *str1_val)
{
    printf("%s() %s\n", str0_val, str1_val);
}

void PhwangClass::phwangLogit3 (char const *str0_val, char const *str1_val, char const *str2_val)
{
    printf("%s() %s {%s}\n", str0_val, str1_val, str2_val);
}

void PhwangClass::phwangAbend (char const *str0_val, char const *str1_val)
{
    printf("*****abend*****%s() %s\n", str0_val, str1_val);
    int *junk = 0;
    *junk = 0;
}

void PhwangClass::phwangAbend3 (char const *str0_val, char const *str1_val, char const *str2_val)
{
    printf("*****abend*****%s() %s, %s\n", str0_val, str1_val, str2_val);
    int *junk = 0;
    *junk = 0;
}

void PhwangClass::logit (char const *str0_val, char const *str1_val) {
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    this->phwangLogit(s, str1_val);
}

void PhwangClass::abend (char const *str0_val, char const *str1_val) {
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    this->phwangAbend(s, str1_val);
}

void PhwangClass::abend3 (char const *str0_val, char const *str1_val, char const *str2_val) {
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    this->phwangAbend3(s, str1_val, str2_val);
}

void PhwangClass::printBoard (char const* data_val, int board_size_val)
{
    int i = strlen(data_val);
    while (i) {
        if (*data_val == '0') {
            printf(" +");
        }
        else if (*data_val == '1') {
            printf(" *");
        }
        else if (*data_val == '2') {
            printf(" O");
        }
        data_val++;
        i--;
        if (i % board_size_val == 0) {
            printf("\n");
        }
    }
}

/**************************************************************************************************************/
/**************************************************************************************************************/
/**************************************************************************************************************/

#define PHWNAG_CLASS_MALLOC_MARKER "phwang"
#define PHWNAG_CLASS_MALLOC_MARKER_SIZE 6
#define PHWNAG_CLASS_MALLOC_LENGTH_SIZE 4
#define PHWNAG_CLASS_MALLOC_WHO_SIZE (4 + 1)
#define PHWNAG_CLASS_MALLOC_HEADER_SIZE (PHWNAG_CLASS_MALLOC_MARKER_SIZE + PHWNAG_CLASS_MALLOC_LENGTH_SIZE + PHWNAG_CLASS_MALLOC_WHO_SIZE)
#define PHWNAG_CLASS_MALLOC_TAILER_SIZE PHWNAG_CLASS_MALLOC_MARKER_SIZE
#define PHWNAG_CLASS_MALLOC_EXTRA_BUFFER_SIZE (PHWNAG_CLASS_MALLOC_HEADER_SIZE + PHWNAG_CLASS_MALLOC_TAILER_SIZE + 8)

void *PhwangClass::phwangMalloc (int size_val, char const *who_val)
{
    char *buf = (char *) malloc(size_val + PHWNAG_CLASS_MALLOC_EXTRA_BUFFER_SIZE);
    memcpy(buf, PHWNAG_CLASS_MALLOC_MARKER, PHWNAG_CLASS_MALLOC_MARKER_SIZE);
    this->encodeNumber(buf + PHWNAG_CLASS_MALLOC_MARKER_SIZE, size_val, PHWNAG_CLASS_MALLOC_LENGTH_SIZE);
    strcpy(buf + PHWNAG_CLASS_MALLOC_MARKER_SIZE + PHWNAG_CLASS_MALLOC_LENGTH_SIZE, who_val);
    memcpy(buf + PHWNAG_CLASS_MALLOC_HEADER_SIZE + size_val, PHWNAG_CLASS_MALLOC_MARKER, PHWNAG_CLASS_MALLOC_MARKER_SIZE);
    return buf + PHWNAG_CLASS_MALLOC_HEADER_SIZE;
}

void PhwangClass::phwangFree (void *data_val, char const *who_val)
{
    if (!data_val) {
        this->abend3("phwangFree", "null data", who_val);
        return;
    }

    char *buf = ((char *) data_val) - PHWNAG_CLASS_MALLOC_HEADER_SIZE;

    if (memcmp(buf, PHWNAG_CLASS_MALLOC_MARKER, PHWNAG_CLASS_MALLOC_MARKER_SIZE)) {
        this->abend3("phwangFree Head", who_val, buf + PHWNAG_CLASS_MALLOC_MARKER_SIZE + PHWNAG_CLASS_MALLOC_LENGTH_SIZE);
        return;
    }

    int length = this->decodeNumber(buf + PHWNAG_CLASS_MALLOC_MARKER_SIZE, PHWNAG_CLASS_MALLOC_LENGTH_SIZE);

    if (memcmp(data_val + length, PHWNAG_CLASS_MALLOC_MARKER, PHWNAG_CLASS_MALLOC_MARKER_SIZE)) {
        this->abend3("phwangFree Tail", who_val, buf + PHWNAG_CLASS_MALLOC_MARKER_SIZE + PHWNAG_CLASS_MALLOC_LENGTH_SIZE);
        return;
    }

    free(buf);
}

/**************************************************************************************************************/
/**************************************************************************************************************/
/**************************************************************************************************************/

void PhwangClass::encodeNumber (char *str_val, int number_val, int size_val)
{
    str_val[size_val] = 0;
    while (size_val > 0) {
        size_val--;
        str_val[size_val] = '0' + number_val % 10;
        number_val /= 10;
    }
}

int PhwangClass::decodeNumber (char const *str_val, int size_val)
{
    int number = 0;
    int factor = 1;

    //printf("decodeNumber() input=%s\n", str_val);
    while (size_val > 0) {
        size_val--;
        number += (str_val[size_val] - '0') * factor;
        factor *= 10;
    }
    //printf("decodeNumber() output=%d\n", number);
    return number;
}

void PhwangClass::encodeIdIndex (char *str_val, int id_val, int id_size_val, int index_val, int index_size_val)
{
    encodeNumber(str_val, id_val, id_size_val);
    encodeNumber(str_val + id_size_val, index_val, index_size_val);
}

void PhwangClass::decodeIdIndex (char const *str_val, int *id_ptr_val, int id_size_val, int *index_ptr_val, int index_size_val)
{
    *id_ptr_val = decodeNumber(str_val, id_size_val);
    *index_ptr_val = decodeNumber(str_val + id_size_val, index_size_val);
}

/**************************************************************************************************************/
/**************************************************************************************************************/
/**************************************************************************************************************/

void *PhwangClass::listMgrMalloc (char const *caller_name_val, int id_size_val, int index_size_val, int global_entry_id_val)
{
    ListMgrClass *list_mgr = new ListMgrClass(caller_name_val, id_size_val, index_size_val, global_entry_id_val);
    return list_mgr;
}

void PhwangClass::listMgrFree (void *list_mgr_val)
{
    if (!list_mgr_val) {
        this->abend("listMgrFree", "null list_mgr_val");
        return;
    }

    if (strcmp(((ListMgrClass *) list_mgr_val)->objectName(), "ListMgrClass")) {
        char s[LOGIT_BUF_SIZE];
        sprintf(s, "wrong object: objectName=%s", ((ListMgrClass *) list_mgr_val)->objectName());
        this->abend("listMgrFree", s);
        return;
    }

    ((ListMgrClass *) list_mgr_val)->~ListMgrClass();
}

void PhwangClass::listMgrRemoveEntry (void *list_mgr_val, void *entry_val)
{
    if (!list_mgr_val) {
        this->abend("listMgrRemoveEntry", "null list_mgr_val");
        return;
    }

    if (strcmp(((ListMgrClass *) list_mgr_val)->objectName(), "ListMgrClass")) {
        char s[LOGIT_BUF_SIZE];
        sprintf(s, "wrong object: objectName=%s", ((ListMgrClass *) list_mgr_val)->objectName());
        this->abend("listMgrRemoveEntry", s);
        return;
    }

    ((ListMgrClass *) list_mgr_val)->removeEntry((ListEntryClass *) entry_val);
}

void *PhwangClass::listMgrSearchEntry(void *list_mgr_val, char const *data_val, void *extra_data_val)
{
    if (!list_mgr_val) {
        this->abend("listMgrSearchEntry", "null list_mgr_val");
        return 0;
    }

    if (strcmp(((ListMgrClass *) list_mgr_val)->objectName(), "ListMgrClass")) {
        char s[LOGIT_BUF_SIZE];
        sprintf(s, "wrong object: objectName=%s", ((ListMgrClass *) list_mgr_val)->objectName());
        this->abend("listMgrSearchEntry", s);
        return 0;
    }

    return ((ListMgrClass *) list_mgr_val)->searchEntry(data_val, extra_data_val);
}

int PhwangClass::listMgrGetMaxIndex (void *list_mgr_val, char const *who_val)
{
    if (!list_mgr_val) {
        this->abend("listMgrGetMaxIndex", "null list_mgr_val");
        return 0;
    }

    if (strcmp(((ListMgrClass *) list_mgr_val)->objectName(), "ListMgrClass")) {
        char s[LOGIT_BUF_SIZE];
        sprintf(s, "wrong object: who=%s objectName=%s", who_val, ((ListMgrClass *) list_mgr_val)->objectName());
        this->abend("listMgrGetMaxIndex", s);
        return 0;
    }

    return ((ListMgrClass *) list_mgr_val)->maxIndex();
}

void *PhwangClass::listMgrGetEntryTableArray (void *list_mgr_val)
{
    if (!list_mgr_val) {
        this->abend("listMgrGetEntryTableArray", "null list_mgr_val");
        return 0;
    }

    if (strcmp(((ListMgrClass *) list_mgr_val)->objectName(), "ListMgrClass")) {
        char s[LOGIT_BUF_SIZE];
        sprintf(s, "wrong object: objectName=%s", ((ListMgrClass *) list_mgr_val)->objectName());
        this->abend("listMgrGetEntryTableArray", s);
        return 0;
    }

    return ((ListMgrClass *) list_mgr_val)->entryTableArray();
}

/**************************************************************************************************************/
/**************************************************************************************************************/
/**************************************************************************************************************/

void *PhwangClass::arrayMgrMalloc(char const *caller_name_val, char array_type_val, int array_size_val)
{
    ArrayMgrClass *array_mgr = new ArrayMgrClass(caller_name_val, array_type_val, array_size_val);
    return array_mgr;
}

void PhwangClass::arrayMgrFree(void *array_mgr_val)
{
    if (!array_mgr_val) {
        this->abend("arrayMgrFree", "null array_mgr_val");
        return;
    }

    if (strcmp(((ArrayMgrClass *) array_mgr_val)->objectName(), "ArrayMgrClass")) {
        this->abend("arrayMgrFree", "wrong object");
        return;
    }

    ((ArrayMgrClass *) array_mgr_val)->~ArrayMgrClass();
}

void PhwangClass::arrayMgrInsertElement(void *array_mgr_val, void *element_val)
{
    if (!array_mgr_val) {
        this->abend("arrayMgrInsertElement", "null array_mgr_val");
        return;
    }

    if (strcmp(((ArrayMgrClass *) array_mgr_val)->objectName(), "ArrayMgrClass")) {
        this->abend("arrayMgrInsertElement", "wrong object");
        return;
    }

    ((ArrayMgrClass *) array_mgr_val)->insertElement(element_val);
}

void PhwangClass::arrayMgrRemoveElement(void *array_mgr_val, void *element_val)
{
    if (!array_mgr_val) {
        this->abend("arrayMgrRemoveElement", "null array_mgr_val");
        return;
    }

    if (strcmp(((ArrayMgrClass *) array_mgr_val)->objectName(), "ArrayMgrClass")) {
        this->abend("arrayMgrRemoveElement", "wrong object");
        return;
    }

    ((ArrayMgrClass *) array_mgr_val)->removeElement(element_val);
}

void *PhwangClass::arrayMgrGetArrayTable(void *array_mgr_val, int *array_size_ptr)
{
    if (!array_mgr_val) {
        this->abend("arrayMgrGetArrayTable", "null array_mgr_val");
        return 0;
    }

    if (strcmp(((ArrayMgrClass *) array_mgr_val)->objectName(), "ArrayMgrClass")) {
        this->abend("arrayMgrGetArrayTable", "wrong object");
        return 0;
    }

    return ((ArrayMgrClass *) array_mgr_val)->getArrayTable(array_size_ptr);
}

/**************************************************************************************************************/
/**************************************************************************************************************/
/**************************************************************************************************************/

void *PhwangClass::mallocQueue (int do_suspend_val, int max_size_val)
{
    QueueClass *queue = new QueueClass(do_suspend_val, max_size_val);
    return queue;
}

void PhwangClass::freeQueue (void *queue_val)
{
    if (!queue_val) {
        this->abend("freeQueue", "null queue_val");
        return;
    }

    if (strcmp(((QueueClass *) queue_val)->objectName(), "QueueClass")) {
        this->abend("freeQueue", "wrong object");
        return;
    }

    delete (QueueClass *) queue_val;
}

void PhwangClass::enqueue (void *queue_val, void *data_val)
{
    if (!queue_val) {
        this->abend("enqueue", "null queue_val");
        return;
    }

    if (strcmp(((QueueClass *) queue_val)->objectName(), "QueueClass")) {
        this->abend("enqueue", "wrong object");
        return;
    }

    ((QueueClass *) queue_val)->enqueueData(data_val);
}

void *PhwangClass::dequeue (void *queue_val)
{
    if (!queue_val) {
        this->abend("dequeue", "null queue_val");
        return 0;
    }

    if (strcmp(((QueueClass *) queue_val)->objectName(), "QueueClass")) {
        this->abend("dequeue", "wrong object");
        return 0;
    }

    return ((QueueClass *) queue_val)->dequeueData();
}

/**************************************************************************************************************/
/**************************************************************************************************************/
/**************************************************************************************************************/

void *PhwangClass::mallocTpServer (
                        void *caller_object_val,
                        unsigned short port_val,
                        void (*accept_callback_func_val)(void *, void *),
                        void *accept_callback_parameter_val,
                        void (*receive_callback_func_val)(void *, void *, void *),
                        void *receive_callback_parameter_val,
                        char const *who_val)
{
    TpServerClass *tp_server_object = new TpServerClass(
                    caller_object_val,
                    port_val,
                    accept_callback_func_val,
                    accept_callback_parameter_val,
                    receive_callback_func_val,
                    receive_callback_parameter_val,
                    who_val);

    if (tp_server_object) {
        tp_server_object->startServerThread();
    }
    return tp_server_object;
}

void *PhwangClass::tpConnect (
                    unsigned long ip_addr_val, 
                    unsigned short port_val, 
                    void (*receive_callback_val)(void *, void *, void *), 
                    void *receive_object_val,
                    char const *who_val)
{
    return globalTpConnect (
                ip_addr_val, 
                port_val, 
                receive_callback_val, 
                receive_object_val,
                who_val);
}

void PhwangClass::freeTpServer (void *tp_server_object_val)
{
    if (!tp_server_object_val) {
        this->abend("phwangFreeTpTransfer", "null tp_server_object_val");
        return;
    }

    if (strcmp(((TpServerClass *) tp_server_object_val)->objectName(), "TpServerClass")) {
        this->abend("phwangFreeTpTransfer", "wrong object");
        return;
    }

    delete (TpServerClass *) tp_server_object_val;
}

void PhwangClass::freeTpTransfer (void *tp_transfer_object_val)
{
    if (!tp_transfer_object_val) {
        this->abend("phwangFreeTpTransfer", "null tp_transfer_object_val");
        return;
    }

    if (strcmp(((TpTransferClass *) tp_transfer_object_val)->objectName(), "TpTransferClass")) {
        this->abend("phwangFreeTpTransfer", "wrong object");
        return;
    }

    delete (TpTransferClass *) tp_transfer_object_val;
}

void PhwangClass::tpTransmit (void *tp_transfer_object_val, char *data_val)
{
    if (!tp_transfer_object_val) {
        this->abend("phwangTpTransmit", "null tp_transfer_object_val");
        return;
    }

    if (strcmp(((TpTransferClass *) tp_transfer_object_val)->objectName(), "TpTransferClass")) {
        this->abend("phwangTpTransmit", "wrong object");
        return;
    }

    ((TpTransferClass *) tp_transfer_object_val)->exportTransmitData(data_val);
}

/*
void PhwangClass::createDbDb(char *db_val)
{
    createPostgreDb(db_val);
}
*/

/*
void PhwangClass::createDbTable(char *table_val)
{
    createPostgreTable(table_val);
}
*/

void PhwangClass::registerProgramProcess(int *register_tag_ptr_val, char *program_name_val, unsigned short port_val)
{
    *register_tag_ptr_val = 1;
    while (*register_tag_ptr_val) {
        sleep(10);
    }
}
