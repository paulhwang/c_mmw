/*
  Copyrights reserved
  Written by Paul Hwang
  File name: mmw_frame_class.h
*/

#pragma once

#define MMW_FRAME_CLASS_MAX_ARRAY_SIZE 200
#define MMW_FRAME_CLASS_TYPE_HEADER 0
#define MMW_FRAME_CLASS_TYPE_NORMAL 1
#define MMW_FRAME_CLASS_TYPE_ACTIVE 2

class MmwFrameClass {
    int theMaxArraySize;
    int theArraySize;
    char **theLineArray;
    int theFrameType;


    int theFrameNumberIndex;
    int theFrameNumber;
    char *frameNumberStr(void) { return this->theLineArray[0] + this->theFrameNumberIndex; }
    int thePointNumberIndex;
    int thePointNumber;
    char *pointeNumberStr(void) { return this->theLineArray[1] + this->thePointNumberIndex; }
    char **clouePointStrArray(void) { return &this->theLineArray[2]; }
    char **targetStrArray(void) { return &this->theLineArray[2 + this->thePointNumber]; }
    char *idleMappingStr(void) { return this->targetStrArray()[13]; }
    char *activeMappingStr(void) { return this->targetStrArray()[16]; }

    void parseHeaderFrame(void);
    void parseNormalFrame(void);
    void parseIdleFrame(void);
    void parseActiveFrame(void);

    void debug(int on_off_val, char const *str0_val, char const *str1_val) { if (on_off_val) this->logit(str0_val, str1_val); };
    void logit(char const *str0_val, char const *str1_val);
    void abend(char const *str0_val, char const *str1_val);

  public:
    int arraySize(void) { return this->theArraySize; }
    char **lineArray(void) { return this->theLineArray; }
    char *lineArrayElement(int index_val) { return this->theLineArray[index_val]; }
    void addLineArrayElement(char *data_val) { this->theLineArray[this->theArraySize] = data_val; this->theArraySize++; }

    void printFrameArrayBrief(void) { printf("###%s\n", this->theLineArray[0]); }
    void printFrameArray(void) {
        printf("\n*****************************\n");
        for (int i = 0; i < this->theArraySize; i++) {
            printf("###%s\n", this->theLineArray[i]);
        }
    }

    int frameTypeActive(void) { return this->theFrameType == MMW_FRAME_CLASS_TYPE_ACTIVE; }
    int floatingData(void) { return memcmp(this->targetStrArray()[0], "[[ 0. ", 6) != 0; }
    void parseFrame(void);
    char *generateData(void);

    MmwFrameClass(void);
    ~MmwFrameClass(void);
    char const *objectName(void) {return "MmwFrameClass";}
};
