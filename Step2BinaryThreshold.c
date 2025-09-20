#include "Step2BinaryThreshold.h"

void toBinaryScale(unsigned char input_image[BMP_WIDTH][BMP_HEIGTH]) {
    for (int x=0; x < BMP_WIDTH; x++) {
        for (int y=0; y < BMP_HEIGTH; y++) {
            input_image[x][y] = input_image[x][y] < THRESHOLD ? 0 : 255;
        }
    }
}