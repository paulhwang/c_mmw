# Copyrights reserved
# Written by Paul Hwang

include Makefile.inc

SERVER_PROJ_DIR = server_proj_dir
CLIENT_PROJ_DIR = client_proj_dir
PHWANG_DIR = phwang_dir
INCLUDE_DIR = include_dir
PROTOCOL_DIR = $(INCLUDE_DIR)/protocol_dir
JSON_DIR          = $(PHWANG_DIR)/json_dir
SUSPEND_DIR       = $(PHWANG_DIR)/suspend_dir
LIST_MGR_DIR      = $(PHWANG_DIR)/list_mgr_dir
ARRAY_MGR_DIR     = $(PHWANG_DIR)/array_mgr_dir
ID_INDEX_LIST_DIR = $(PHWANG_DIR)/id_index_list_dir
QUEUE_DIR         = $(PHWANG_DIR)/queue_dir
NET_DIR      = $(PHWANG_DIR)/net_dir





SERVER_DIR   = $(SERVER_PROJ_DIR)/server_dir



SON_OBJS = $(JSON_DIR)/json_class.o 
SUSPEND_OBJS = $(SUSPEND_DIR)/suspend_class.o 
LIST_MGR_OBJS = $(LIST_MGR_DIR)/list_mgr_class.o $(LIST_MGR_DIR)/list_entry_class.o
ARRAY_MGR_OBJS = $(ARRAY_MGR_DIR)/array_mgr_class.o
ID_INDEX_LIST_OBJS = $(ID_INDEX_LIST_DIR)/id_index_list_class.o 
QUEUE_OBJS = $(QUEUE_DIR)/queue_entry_class.o $(QUEUE_DIR)/queue_class.o
NET_OBJS = $(NET_DIR)/tp_server_class.o $(NET_DIR)/tp_transfer_class.o $(NET_DIR)/tp_transfer_class_transmit.o $(NET_DIR)/tp_transfer_class_receive.o  $(NET_DIR)/tp_connect.o 
DB_OBJS = $(DB_DIR)/db_root_class.o $(DB_DIR)/db_postgre.o
PHWANG_OBJS = $(PHWANG_DIR)/phwang.o $(PHWANG_DIR)/phwang_class.o $(JSON_OBJS) $(SUSPEND_OBJS) $(LIST_MGR_OBJS) $(ARRAY_MGR_OBJS) $(ID_INDEX_LIST_OBJS) $(QUEUE_OBJS) $(NET_OBJS)

SERVER_OBJS = $(SERVER_DIR)/server_main.o $(SERVER_DIR)/server_root_class.o
SERVER_PROJ_OBJS = $(SERVER_OBJS)

SERVER = server
ALL_SERVER_OBJS	= $(PHWANG_OBJS) $(SERVER_PROJ_OBJS)

all:	$(SERVER) 

$(SERVER): $(ALL_SERVER_OBJS) 
	$(CC) -o $(SERVER) $(ALL_SERVER_OBJS) -lstdc++ -pthread

clean:
	$(ECHO) cleaning up in .
	- $(RM) $(SERVER) $(CLIENT) $(ALL_SERVER_OBJS) $(ALL_CLIENT_OBJS) $(UTILS_OBJLIBS) $(GO_ROOT_OBJLIBS)
