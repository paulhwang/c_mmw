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

    void readInput(char const *filename_ptr);
    FILE *openFile(char const *filename_val, char const *mode_val);
    MmwFrameClass *readFrame(FILE *fp_val);
    void readNonemptyLine(FILE *fp_val, char *buf_val);
    void readLine(FILE *fp_val, char *buf_val);

    void debug(int on_off_val, char const *str0_val, char const *str1_val) {if (on_off_val) this->logit(str0_val, str1_val);};
    void logit(char const *str0_val, char const *str1_val);
    void abend(char const *str0_val, char const *str1_val);

  public:
    MmwInputClass(MmwClass *mmw_object_val);
    ~MmwInputClass(void);
    char const *objectName(void) {return "MmwInputClass";}
};
