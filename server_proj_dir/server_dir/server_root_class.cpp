/*
  Copyrights reserved
  Written by Paul Hwang
  File name: server_root_class.cpp
*/

#include "../../phwang_dir/phwang.h"
//#include "../../phwang_dir/db_dir/db_root_class.h"
//#include "../fabric_dir/fabric_class.h"
//#include "../engine_dir/engine_class.h"
//#include "../theme_dir/theme_class.h"
#include "server_root_class.h"

ServerRootClass::ServerRootClass (void)
{
    this->logit("ServerRootClass", "start");
    //this->theDbRootObject = new DbRootClass();
    //this->theFabricObject = new FabricClass();
    //this->theGoThemeObject = new ThemeClass();
    //this->theEngineObject = new EngineClass();
}

ServerRootClass::~ServerRootClass (void)
{
    //this->theEngineObject->~EngineClass();
    //this->theGoThemeObject->~ThemeClass();
    //this->theFabricObject->~FabricClass();
    //this->debug(true, "~ServerRootClass", "exit");
}

void ServerRootClass::logit (char const *str0_val, char const *str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangLogit(s, str1_val);
}

void ServerRootClass::abend (char const *str0_val, char const *str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    //phwangAbend(s, str1_val);
}
