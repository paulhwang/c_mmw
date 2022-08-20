/*
  Copyrights reserved
  Written by Paul Hwang
  File name: mmw_input_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "mmw_input_class.h"

MmwInputClass::MmwInputClass (MmwClass *mmw_object_val)
{
    this->debug(true, "MmwInputClass", "start");
    this->theMmwObject = mmw_object_val;

    this->readInput();
}

MmwInputClass::~MmwInputClass (void)
{
    this->debug(true, "~MmwInputClass", "exit");
}

void MmwInputClass::readInput() {
    FILE *fp = this->openFile("data/walking_around.txt", "r");
    if (fp == 0) {
        this->logit("openFile", "cannot open file");
        return;
    }

    char buf[1024];

    for (int i = 0; i < 30; i++) {
        int index = 0;

        while (1) {
            int c = getc(fp);
            if (c == 13) {
                continue;
            }

            if (c == 10) {
                buf[index] = 0;
                break;
            }

            buf[index++] = c;
         }

        //int ii = fscanf(fp, "aaa %i\n", strlen(buf);
        printf("%s\n", buf);
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
