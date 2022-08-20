/*
  Copyrights reserved
  Written by Paul Hwang
  File name: mmw_frame_class.h
*/

#pragma once

#define MMW_FRAME_CLASS_MAX_ARRAY_SIZE 200

class MmwFrameClass {
    int const theMaxArraySize = MMW_FRAME_CLASS_MAX_ARRAY_SIZE;
    int theArraySize;
    char **theLineArray;

    void debug(int on_off_val, char const *str0_val, char const *str1_val) { if (on_off_val) this->logit(str0_val, str1_val); };
    void logit(char const *str0_val, char const *str1_val);
    void abend(char const *str0_val, char const *str1_val);

  public:
    int arraySize(void) { return this->theArraySize; }
    char **lineArray(void) { return this->theLineArray; }
    char *lineArrayElement(int index_val) { return this->theLineArray[index_val]; }
    void addLineArrayElement(char *data_val) { this->theLineArray[this->theArraySize] = data_val; this->theArraySize++; }

    void printFrameArray(void) {
        for (int i = 0; i < this->theArraySize; i++) {
            printf("%s\n", this->theLineArray[i]);
        }
    }

    MmwFrameClass(void);
    ~MmwFrameClass(void);
    char const *objectName(void) {return "MmwFrameClass";}
};
