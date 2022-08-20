/*
  Copyrights reserved
  Written by Paul Hwang
  File name: mmw_input_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "mmw_input_class.h"
#include "mmw_frame_class.h"

MmwInputClass::MmwInputClass (MmwClass *mmw_object_val)
{
    this->debug(true, "MmwInputClass", "start");
    this->theMmwObject = mmw_object_val;

    this->readInput("data/walking_around.txt");
}

MmwInputClass::~MmwInputClass (void)
{
    this->debug(true, "~MmwInputClass", "exit");
}

void MmwInputClass::readInput(char const *filename_ptr) {
    FILE *fp = this->openFile(filename_ptr, "r");
    if (fp == 0) {
        this->logit("openFile", "cannot open file");
        return;
    }
    
    MmwFrameClass *frame_object = this->readFrame(fp);
    frame_object->printFrameArray();
    delete frame_object;
}

MmwFrameClass *MmwInputClass::readFrame(FILE *fp_val) {
    MmwFrameClass *frame_object = new MmwFrameClass();
    char last_frame_buf[1026];
    int not_frame = 1;

    while (1) {
        char buf[1024];

        this->readNonemptyLine(fp_val, buf);
        printf("=%s\n", buf);
        if (memcmp(buf, "frameNum", 7) == 0) {
            strcpy(last_frame_buf, buf);
            not_frame = 0;
            return frame_object;
        }

        char *line_data = (char *) malloc(strlen(buf) + 1);
        strcpy(line_data, buf);
        frame_object->addLineArrayElement(line_data);
    }
}


void MmwInputClass::readNonemptyLine(FILE *fp_val, char *buf_val) {
    while (1) {
        this->readLine(fp_val, buf_val);
        if (buf_val[0]) {
            return;
        }
    }
}


void MmwInputClass::readLine(FILE *fp_val, char *buf_val) {
    int index = 0;

    while (1) {
        int c = getc(fp_val);
        if (c == 13) {
            continue;
        }

        if (c == 10) {
            buf_val[index] = 0;
            break;
        }

        buf_val[index++] = c;
     }
}

FILE *MmwInputClass::openFile(char const *filename_val, char const *mode_val)
{
    FILE *fp;

    fp = fopen(filename_val, mode_val);
    if (fp == 0) {
        this->logit("openFile", "cannot open file");
        return 0;
    }

    return fp;
}

void MmwInputClass::logit (char const *str0_val, char const *str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangLogit(s, str1_val);
}

void MmwInputClass::abend (char const *str0_val, char const *str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    //phwangAbend(s, str1_val);
}
