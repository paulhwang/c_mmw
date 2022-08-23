/*
  Copyrights reserved
  Written by Paul Hwang
  File name: mmw_thread.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "mmw_class.h"
#include "mmw_input_class.h"
#include "mmw_frame_class.h"

void *MmwClassInputThreadFunction (void *fabric_object_val)
{
    ((MmwClass *) fabric_object_val)->inputThreadFunction();
}

void MmwClass::startInputThread (void)
{
    this->debug(false, "startInputThread", "");

    int r = pthread_create(&this->theInputThread, 0, MmwClassInputThreadFunction, this);
    if (r) {
        this->logit("startInputThread", "fail");
        return;
    }
}

void MmwClass::inputThreadFunction (void)
{
    this->debug(false, "inputThreadFunction", "");

    int open_result = this->mmwInputObject()->openFile("../data/mmw_data.txt", "r");
    if (open_result == -1) {
        this->logit("openFile", "cannot open file");
        return;
    }

    int eof;
    MmwFrameClass *frame_object;

    /* read header first */
    frame_object = this->mmwInputObject()->readFrame(&eof);

    if (frame_object) {
        frame_object->printFrameArray();
        delete frame_object;
    }
    if (eof) {
        return;
    }

    while (1) {
        frame_object = this->mmwInputObject()->readFrame(&eof);

        if (frame_object) {
            frame_object->printFrameArrayBrief();
            frame_object->parseFrame();
            if (frame_object->frameTypeActive()) {
                if (!frame_object->floatingData()) {
                    phwangEnqueue(this->theInputQueue, frame_object->generateData());
                }
                delete frame_object;
            }
        }

        if (eof) {
            //printf("*********************EOF************\n");
            break;
        }
    }

    while (1) {
        char *data = this->readInputData();
        printf("data=%s\n", data);
    }
}
