#include "Step3Erode.h"

char safe_get_erd(int i, int j, unsigned char arr[BMP_WIDTH][BMP_HEIGTH]) {
    if (i<0 || i>=BMP_WIDTH || j<0 ||j>=BMP_HEIGTH) {
        return 255;
    }
    return arr[i][j];
}

void erode(unsigned char input_image[BMP_WIDTH][BMP_HEIGTH]) {
    for (int i=0; i<=BMP_WIDTH; i++) {
        for (int j=0; j<=BMP_HEIGTH; j++) {
            if (input_image[i][j]==255) {
                if (safe_get_erd(i+1, j, input_image)==0 || 
                    safe_get_erd(i-1, j, input_image)==0 || 
                    safe_get_erd(i, j+1, input_image)==0 || 
                    safe_get_erd(i, j-1, input_image)==0) {
                    input_image[i][j] = 0;
                }
            }
        }
    }
}