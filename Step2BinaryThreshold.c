#include "Step2BinaryThreshold.h"

void toBinaryScale(unsigned char input_image[BMP_WIDTH][BMP_HEIGTH]) {
    for (int i=0; i <= BMP_WIDTH; i++) {
        for (int j=0; j <= BMP_HEIGTH; j++) {
            input_image[i][j] = input_image[i][j] < THRESHOLD ? 0 : 255;
        }
    }
}