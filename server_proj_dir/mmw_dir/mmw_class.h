/*
  Copyrights reserved
  Written by Paul Hwang
  File name: mmw_class.h
*/

#pragma once

class ServerRootClass;
class MmwInputClass;

class MmwClass {
    ServerRootClass *theServerRootObject;
    MmwInputClass *theMmwInputObject;

    void debug(int on_off_val, char const *str0_val, char const *str1_val) {if (on_off_val) this->logit(str0_val, str1_val);};
    void logit(char const *str0_val, char const *str1_val);
    void abend(char const *str0_val, char const *str1_val);

  public:
    MmwClass(ServerRootClass *server_root_object_val);
    ~MmwClass(void);
    char const *objectName(void) {return "MmwClass";}
};
