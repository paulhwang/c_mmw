/*
  Copyrights reserved
  Written by Paul Hwang
  File name: mmw_frame_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "mmw_frame_class.h"

MmwFrameClass::MmwFrameClass (void)
{
    this->debug(false, "MmwFrameClass", "start");

    memset(this, 0, sizeof(*this));
    this->theMaxArraySize = MMW_FRAME_CLASS_MAX_ARRAY_SIZE;
    //this->theFrameNumberIndex = 0;
    //this->thePointNumberIndex = 0;
    //this->theArraySize = 0;
    this->theLineArray = (char **) malloc(sizeof(char *) * this->theMaxArraySize);
    memset(this->theLineArray, 0, sizeof(char *) * this->theMaxArraySize);
}

MmwFrameClass::~MmwFrameClass (void)
{
    this->debug(false, "~MmwFrameClass", "start");
    for (int i = 0; i < this->theArraySize; i++) {
        if (this->theLineArray[i]) {
            free(this->theLineArray[i]);
            this->theLineArray[i] = 0;
        }
    }
    free(this->theLineArray);
}

void MmwFrameClass::parseFrame (void)
{
    if (memcmp(this->theLineArray[0], "frameNum: ", 10) == 0) {
        this->theFrameNumberIndex = 10;
        this->theFrameNumber = phwangDecodeNumber(this->frameNumberStr(), strlen(this->frameNumberStr()));
        //printf("%i\n", this->theFrameNumber);
        this->parseNormalFrame();
    }
    else {
        this->parseHeaderFrame();
    }
}


void MmwFrameClass::parseHeaderFrame (void)
{
    this->theFrameType = MMW_FRAME_CLASS_TYPE_HEADER;
}

void MmwFrameClass::parseNormalFrame (void)
{
    this->theFrameType = MMW_FRAME_CLASS_TYPE_NORMAL;
    this->debug(false, "porcessNormalFrame", this->frameNumberStr());

    if (memcmp(this->pointeNumberStr(), " PointNumber: ", 14) != 0) {
        this->abend("porcessNormalFrame", "ointeNumber not match");
        return;
    }

    this->thePointNumberIndex = 14;
    this->thePointNumber = phwangDecodeNumber(this->pointeNumberStr(), strlen(this->pointeNumberStr()));
    //printf("thePointNumber=%i\n", this->thePointNumber);
    this->debug(false, "porcessNormalFrame", this->pointeNumberStr());

    //printf("targetStr=%s\n", this->targetStrArray()[0]);
    //printf("idleMappingStr=%s\n", this->idleMappingStr());

    if (memcmp(this->idleMappingStr(), "[]", 2) == 0) {
        this->parseIdleFrame();
    }
    else {
        this->parseActiveFrame();
    }
}

void MmwFrameClass::parseIdleFrame (void)
{
    this->debug(true, "parseIdleFrame", this->frameNumberStr());
    //printf("idleMappingStr=%s\n", this->idleMappingStrArray()[0]);
}

void MmwFrameClass::parseActiveFrame (void)
{
    this->theFrameType = MMW_FRAME_CLASS_TYPE_ACTIVE;
    this->debug(true, "parseActiveFrame", this->frameNumberStr());
    //printf("activeMappingStr=%s\n", this->activeMappingStr());
    for (int i = 0; i < 16; i++) {
        //printf("target=%s\n", this->targetStrArray()[i]);
        //printf("target=%s\n", this->targetStrArray()[i] + 2);
    }
}

char *MmwFrameClass::generateData (void)
{
    int buf_len = 1;
    for (int i = 0; i < 4; i++) {
        buf_len += strlen(this->targetStrArray()[i]);
    }

    char *s = (char *) malloc(buf_len);
    s[0] = 0;
    for (int i = 0; i < 4; i++) {
        strcat(s, this->targetStrArray()[i]);
    }
    
    return s;
}

void MmwFrameClass::logit (char const *str0_val, char const *str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangLogit(s, str1_val);
}

void MmwFrameClass::abend (char const *str0_val, char const *str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    //phwangAbend(s, str1_val);
}
