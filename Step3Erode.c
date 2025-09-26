#include "Step3Erode.h"
#include <stdio.h>

const char erosionShape[erosionShapeSize][erosionShapeSize] = {
  {0,1,0},
  {1,1,1},
  {0,1,0}
};

char isOutOfBounds(int x, int y) {
    return x<0 || x>=BMP_WIDTH || y<0 || y>=BMP_HEIGTH;
}

char shouldBeEroded(int x, int y, unsigned char binaryImage[BMP_WIDTH][BMP_HEIGTH]) {
    for (int i=-erosionShapeDiameter; i<=erosionShapeDiameter; i++) {
        for (int j=-erosionShapeDiameter; j<=erosionShapeDiameter; j++) {
            if (erosionShape[i+erosionShapeDiameter][j+erosionShapeDiameter]==0) continue; // don't care about the central pixel

            int neighborX = x + i;
            int neighborY = y + j;
            if (!isOutOfBounds(neighborX, neighborY) && !binaryImage[neighborX][neighborY]) {
                return 1;
            }
        }
    }
    return 0;
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