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
    
    char *first_line = 0;
    MmwFrameClass *frame_object = this->readFrame(fp, &first_line);
    frame_object->printFrameArray();
    delete frame_object;

    frame_object = this->readFrame(fp, &first_line);
    frame_object->printFrameArray();
    delete frame_object;
}

MmwFrameClass *MmwInputClass::readFrame(FILE *fp_val, char **first_line_ptr_val) {
    MmwFrameClass *frame_object = new MmwFrameClass();

    if (*first_line_ptr_val) {
        frame_object->addLineArrayElement(*first_line_ptr_val);
    }

    while (1) {
        char line_buf[1024];

        this->readNonemptyLine(fp_val, line_buf);

        if (strlen(line_buf) == 0) {
            *first_line_ptr_val = 0;
            printf("*********************EOF\n");
            delete frame_object;
            return 0;
        }
        else {
            printf("=%s\n", line_buf);
        }

        char *line_data = (char *) malloc(strlen(line_buf) + 1);
        strcpy(line_data, line_buf);

        if (memcmp(line_buf, "frameNum", 7) == 0) {
            *first_line_ptr_val = line_data;
            return frame_object;
        }

        frame_object->addLineArrayElement(line_data);
    }
}


void MmwInputClass::readNonemptyLine(FILE *fp_val, char *line_buf_val) {
    while (1) {
        this->readLine(fp_val, line_buf_val);
        if (line_buf_val[0]) {
            return;
        }
    }
}


void MmwInputClass::readLine(FILE *fp_val, char *line_buf_val) {
    int index = 0;

    while (1) {
        int c = getc(fp_val);
        if (c == 13) {
            continue;
        }

        if (c == 10) {
            line_buf_val[index] = 0;
            break;
        }

        line_buf_val[index++] = c;
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
