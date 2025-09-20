#ifndef STEP4CAPTURE_H
#define STEP4CAPTURE_H

#include "cbmp.h"

#define CAPTURE_SIZE 12
#define HALF_CAPTURE_SIZE (CAPTURE_SIZE / 2)

struct CaptureResult {
    int chords[10000][2];
    int n;
};

void capture(unsigned char input_image[BMP_WIDTH][BMP_HEIGTH], struct CaptureResult result);

#endif