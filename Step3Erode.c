#include "Step3Erode.h"
#include <stdio.h>

char shouldBeEroded(int x, int y, unsigned char binaryImage[BMP_WIDTH][BMP_HEIGTH]) {
    // can be optimized by removing variables
    const char isOutOfBounds = x<0 || x>=BMP_WIDTH || y<0 || y>=BMP_HEIGTH;
    const char isAdjecentToBlack = 
        !binaryImage[x-1][y] ||
        !binaryImage[x+1][y] ||
        !binaryImage[x][y-1] ||
        !binaryImage[x][y+1];
    return !isOutOfBounds && isAdjecentToBlack;
}

char erode(unsigned char binaryImage[BMP_WIDTH][BMP_HEIGTH], unsigned char outputImage[BMP_WIDTH][BMP_HEIGTH]) {
    char isFullyEroded = 1;
    for (int x=0; x<BMP_WIDTH; x++) {
        for (int y=0; y<BMP_HEIGTH; y++) {
            if (binaryImage[x][y]==0)
            {
                outputImage[x][y] = 0;
                continue;
            }

            outputImage[x][y] = !shouldBeEroded(x, y, binaryImage); // 1 if should not be eroded, 0 if should be eroded
            isFullyEroded = 0;
        }
    }
    return isFullyEroded;
}