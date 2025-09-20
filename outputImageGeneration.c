#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> 
#include <outputImageGeneration.h>


static void setPixelColor(unsigned char image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS], int x, int y, uint32_t color
) {
    if (x >= 0 && x < BMP_WIDTH && y >= 0 && y < BMP_HEIGTH) {
        unsigned char r = (unsigned char)((color >> 16) & 0xFF);
        unsigned char g = (unsigned char)((color >>  8) & 0xFF);
        unsigned char b = (unsigned char)((color      ) & 0xFF);
    }
}

static void drawX(
    unsigned char image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS], int xSize, int xCenter, int yCenter
) {
    const int xArmSize = (xSize - 1) / 2;

    for (int offset = -xArmSize; offset <= xArmSize; offset++) {
        int x = xCenter + offset;

        int yUp = yCenter + offset;
        setPixelColor(image, x, yUp, X_COLOR);

        int yDown = yCenter - offset;
        setPixelColor(image, x, yDown, X_COLOR);
    }
}

void generateOutputImage(
    char *outputFilePath, 
    unsigned char originalImageArray[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS],
    int detectedCellsCoordinates[][2],
    int detectedCellsNo
) {
    for (int i = 0; i < detectedCellsNo; i++) {
        const int xCenter = detectedCellsCoordinates[i][0];
        const int yCenter = detectedCellsCoordinates[i][1];
        drawX(originalImageArray, X_SIZE, xCenter, yCenter);

        write_bitmap(originalImageArray, outputFilePath);
    }
}