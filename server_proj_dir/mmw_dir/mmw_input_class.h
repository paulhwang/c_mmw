/*
  Copyrights reserved
  Written by Paul Hwang
  File name: mmw_input_class.h
*/

#pragma once

class MmwClass;
class MmwFrameClass;

class MmwInputClass {
    MmwClass *theMmwObject;
    FILE *theFpInput;
    char *thePrevFrameNum;

    FILE *fpInput(void) { return this->theFpInput; }

    void readNonemptyLine(char *buf_val, int *eof_val);
    void readLine(char *buf_val, int *eof_val);

    void debug(int on_off_val, char const *str0_val, char const *str1_val) {if (on_off_val) this->logit(str0_val, str1_val);};
    void logit(char const *str0_val, char const *str1_val);
    void abend(char const *str0_val, char const *str1_val);

  public:
    int openFile(char const *filename_val, char const *mode_val);
    MmwFrameClass *readFrame(int *eof_val);
    
    MmwInputClass(MmwClass *mmw_object_val);
    ~MmwInputClass(void);
    char const *objectName(void) {return "MmwInputClass";}
};
