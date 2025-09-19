#include "cbmp.h"

#define CAPTURE_SIZE 12 //remove when finished product
#define HALF_CAPTURE_SIZE CAPTURE_SIZE/2

char safeGetCap(int i, int j, char arr[BMP_WIDTH][BMP_HEIGTH]) {
    if (i<0 || i>=BMP_WIDTH || j<0 ||j>=BMP_HEIGTH) {
        return 0;
    }
    return arr[i][j];
}

void erode(unsigned char input_image[BMP_WIDTH][BMP_HEIGTH]) {
    int n = 0;
    int chords[10000][2];
    int p = 0; //pointer
    char detectedOnBorder; //bool
    char detectedInArea; //bool

    for (int i=HALF_CAPTURE_SIZE; i<=BMP_WIDTH-HALF_CAPTURE_SIZE; i++) {
        for (int j=HALF_CAPTURE_SIZE; j<=BMP_HEIGTH-HALF_CAPTURE_SIZE; j++) {

            // Check whether exclusion frame is all black. If not, continue
            for (char k=i-HALF_CAPTURE_SIZE-1; k<=i+HALF_CAPTURE_SIZE+1; k++) {
                if (safeGetCap(k, j+HALF_CAPTURE_SIZE, input_image)==255) {
                    detectedOnBorder = 1;
                    break;
                }
            }
            if (detectedOnBorder) {continue;}
            for (char k=i-HALF_CAPTURE_SIZE-1; k<=i+HALF_CAPTURE_SIZE+1; k++) {
                if (safeGetCap(k, j-HALF_CAPTURE_SIZE, input_image)==255) {
                    detectedOnBorder = 1;
                    break;
                }
            }
            if (detectedOnBorder) {continue;}
            for (char k=j-HALF_CAPTURE_SIZE-1; k<=j+HALF_CAPTURE_SIZE+1; k++) {
                if (safeGetCap(i+HALF_CAPTURE_SIZE, k, input_image)==255) {
                    detectedOnBorder = 1;
                    break;
                }
            }
            if (detectedOnBorder) {continue;}
            for (char k=j-HALF_CAPTURE_SIZE-1; k<=j+HALF_CAPTURE_SIZE+1; k++) {
                if (safeGetCap(i-HALF_CAPTURE_SIZE, k, input_image)==255) {
                    detectedOnBorder = 1;
                    break;
                }
            }
            if (detectedOnBorder) {continue;}

            // Check for one white pixel in detection area
            for (int k=i-HALF_CAPTURE_SIZE; k<=i+HALF_CAPTURE_SIZE; k++) {
                for (int l=j-HALF_CAPTURE_SIZE; l<=j+HALF_CAPTURE_SIZE; l++) {
                    if (input_image[k][l]==255) {
                        detectedInArea = 1;
                        input_image[k][l] = 0;
                    }
                }
            }

            // Count cell
            if (detectedInArea) {
                n++;
                chords[p][0] = i;
                chords[p][1] = j;
                p++;
            }
        }
    }
}