#include <cbmp.h>

#define X_SIZE 13 // size in px
#define X_COLOR 0xff0000 // red


// Public function declarations
void generateOutputImage(
    char * outputFilePath, 
    unsigned char originalImageArray[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS],
    int detectedCellsCoordinates[][2], // array of pairs (x, y)
    int detectedCellsNo
);