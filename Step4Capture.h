#ifndef STEP4CAPTURE_H
#define STEP4CAPTURE_H

#include "cbmp.h"

#define CAPTURE_SIZE 12
#define HALF_CAPTURE_SIZE (CAPTURE_SIZE / 2)

char safeGetCap(int i, int j, char arr[BMP_WIDTH][BMP_HEIGTH]);

void erode(unsigned char input_image[BMP_WIDTH][BMP_HEIGTH]);

#endif