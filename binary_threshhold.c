#include "cbmp.h"
#include "binary_threshold.h"

void binaryThreshold(unsigned char input_image[BMP_WIDTH][BMP_HEIGTH]) {
    for (int i=0; i<=BMP_WIDTH; i++) {
        for (int j=0; j<=BMP_HEIGTH; j++) {
            if (input_image[i][j]<THRESHOLD) {
                input_image[i][j] = 0;
            } else {
                input_image[i][j] = 255;
            }
        }
    }
}