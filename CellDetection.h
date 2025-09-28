#ifndef CELLDETECTION_H
#define CELLDETECTION_H

#include "cbmp.h"
#include "Step1GrayScale.h"
#include "Step2BinaryThreshold.h"
#include "Step3Erode.h"
#include "Step4Capture.h"
#include "Step5MarkingCells.h"

void detectCells(unsigned char input_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS]);
struct CaptureResult erodeAndCaptureAll(unsigned char inputImage[BMP_WIDTH][BMP_HEIGTH]);

#endif