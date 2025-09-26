#ifndef STEP3ERODE_H
#define STEP3ERODE_H

#include "cbmp.h"

#define erosionShapeSize 3
#define erosionShapeDiameter (erosionShapeSize/2) // 1 for size 3, 2 for size 5, etc.

char erode(unsigned char binaryImage[BMP_WIDTH][BMP_HEIGTH], unsigned char outputImage[BMP_WIDTH][BMP_HEIGTH]);

#endif