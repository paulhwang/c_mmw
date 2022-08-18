/*
  Copyrights reserved
  Written by Paul Hwang
  File name: db_root.cpp
*/

#include "../phwang.h"
#include "db_root_class.h"
#include "/usr/include/postgresql/libpq-fe.h"

DbRootClass::DbRootClass (void)
{
    this->theGoConnect = this->connectGoDb();
    if (this->goConnect() == 0) {
        this->abend("connectDbs", "fail to connnect to go_db");
        return;
    }

    this->createTables();
    this->insertAccount(0);
}

DbRootClass::~DbRootClass (void)
{
    PQfinish(this->goConnect());
}
 
void DbRootClass::createTables (void) {
    this->createAccountTable();
    this->createCarTable();
}

void do_exit0(PGconn *conn) {
    
    PQfinish(conn);
}

void do_exit(PGconn *conn, PGresult *res) {
    
    fprintf(stderr, "%s\n", PQerrorMessage(conn));    

    PQclear(res);
    PQfinish(conn);    
}

PGconn *DbRootClass::connectGoDb (void)
{
    int lib_ver = PQlibVersion();

    printf("Version of libpq: %d\n", lib_ver);

    PGconn *conn = PQconnectdb("user=phwang dbname=go_db");
    if (PQstatus(conn) == CONNECTION_BAD) {
        
        fprintf(stderr, "Connection to database failed: %s\n", PQerrorMessage(this->goConnect()));
        do_exit0(conn);
        return 0;
    }

    int ver = PQserverVersion(conn);
    printf("Server version: %d\n", ver);

    char *user = PQuser(conn);
    char *db_name = PQdb(conn);
    char *pswd = PQpass(conn);
    
    printf("User: %s\n", user);
    printf("Database name: %s\n", db_name);
    printf("Password: %s\n", pswd);
    return conn;
}

void DbRootClass::createAccountTable (void)
{
    this->logit("createAccountTable", "");
    PGresult *res = PQexec(this->goConnect(), "DROP TABLE IF EXISTS Accounts");
    
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        do_exit(this->goConnect(), res);
    }
    
    PQclear(res);
    
    res = PQexec(this->goConnect(), "CREATE TABLE Accounts(Id INTEGER PRIMARY KEY," \
        "Name VARCHAR(20), Password VARCHAR(20))");

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        do_exit(this->goConnect(), res); 
    }
    
    PQclear(res);
}


void DbRootClass::insertAccount (char const *str_val) {
    PGresult *res;

    res = PQexec(this->goConnect(), "INSERT INTO Accounts VALUES(1, 'admin','pp123')");
        
    if (PQresultStatus(res) != PGRES_COMMAND_OK) 
        do_exit(this->goConnect(), res);     
    
    PQclear(res);    

   res = PQexec(this->goConnect(), "INSERT INTO Accounts VALUES(2, 'phwang','p123')");
        
    if (PQresultStatus(res) != PGRES_COMMAND_OK) 
        do_exit(this->goConnect(), res);     
    
    PQclear(res);    
}

void DbRootClass::createCarTable(void) {
    this->logit("createCarTable", "");

    PGresult *res = PQexec(this->goConnect(), "DROP TABLE IF EXISTS Cars");
    
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        do_exit(this->goConnect(), res);
    }
    
    PQclear(res);
    
    res = PQexec(this->goConnect(), "CREATE TABLE Cars(Id INTEGER PRIMARY KEY," \
        "Name VARCHAR(20), Price INT)");
        
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        do_exit(this->goConnect(), res); 
    }
    
    PQclear(res);
    
    res = PQexec(this->goConnect(), "INSERT INTO Cars VALUES(1,'Audi',52642)");
        
    if (PQresultStatus(res) != PGRES_COMMAND_OK) 
        do_exit(this->goConnect(), res);     
    
    PQclear(res);    
    
    res = PQexec(this->goConnect(), "INSERT INTO Cars VALUES(2,'Mercedes',57127)");
        
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        do_exit(this->goConnect(), res);   
    }
    
    PQclear(res);    
    
    res = PQexec(this->goConnect(), "INSERT INTO Cars VALUES(3,'Skoda',9000)");
        
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        do_exit(this->goConnect(), res);   
    }
    
    PQclear(res);  
    
    res = PQexec(this->goConnect(), "INSERT INTO Cars VALUES(4,'Volvo',29000)");
        
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        do_exit(this->goConnect(), res);   
    }
    
    PQclear(res);      
    
    res = PQexec(this->goConnect(), "INSERT INTO Cars VALUES(5,'Bentley',350000)");
        
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        do_exit(this->goConnect(), res);   
    }
    
    PQclear(res);  
    
    res = PQexec(this->goConnect(), "INSERT INTO Cars VALUES(6,'Citroen',21000)");
        
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        do_exit(this->goConnect(), res);   
    }
    
    PQclear(res);  
    
    res = PQexec(this->goConnect(), "INSERT INTO Cars VALUES(7,'Hummer',41400)");
        
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        do_exit(this->goConnect(), res);   
    }
    
    PQclear(res);  
    
    res = PQexec(this->goConnect(), "INSERT INTO Cars VALUES(8,'Volkswagen',21600)");
        
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        do_exit(this->goConnect(), res);   
    }
    
    PQclear(res);  
}

void DbRootClass::logit (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangLogit(s, str1_val);
}

void DbRootClass::abend (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangAbend(s, str1_val);
}
