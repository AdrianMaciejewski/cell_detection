#ifndef BLUR_H
#define BLUR_H

#include <stdint.h>
#include <math.h>
#include <string.h>

#include "cbmp.h"



void bgSubtractGaussian(unsigned char input_array[BMP_WIDTH][BMP_HEIGTH], double sigma);

#endif