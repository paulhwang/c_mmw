/*
  Copyrights reserved
  Written by Paul Hwang
  File name: mmw_frame_class.h
*/

#pragma once

class MmwFrameClass {
    int theArraySize;
    char **theLineArray;

    void debug(int on_off_val, char const *str0_val, char const *str1_val) { if (on_off_val) this->logit(str0_val, str1_val); };
    void logit(char const *str0_val, char const *str1_val);
    void abend(char const *str0_val, char const *str1_val);

  public:
    int arraySize(void) { return this->theArraySize; }
    char **lineArray(void) { return this->theLineArray; }
    char *lineArrayElement(int index_val) { return this->theLineArray[index_val]; }
    void incrementArraySize(void) { this->theArraySize++; }
    void addLineArrayElement(char *data_val) { this->theLineArray[this->theArraySize] = data_val; }

    MmwFrameClass(void);
    ~MmwFrameClass(void);
    char const *objectName(void) {return "MmwFrameClass";}
};
