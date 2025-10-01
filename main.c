#include <stdlib.h>
#include <stdio.h>
#include "cbmp.h"
#include "Step1GrayScale.h"
#include "Step2BinaryThreshold.h"
#include "Step3Erode.h"
#include "Step4Capture.h"
#include "Step5MarkingCells.h"
#include "Blur.h"


struct CaptureResult erodeAndCaptureAll(unsigned char inputImage[BMP_WIDTH][BMP_HEIGTH])
{
  struct CaptureResult result = { .n = 0 };
  
  unsigned char (*inputImagePtr)[BMP_HEIGTH] = inputImage;
  
  unsigned char outputImage[BMP_WIDTH][BMP_HEIGTH];
  unsigned char (*outputImagePtr)[BMP_HEIGTH] = outputImage;

  int i=0;
  while (!erode(inputImagePtr, outputImagePtr)) {
      // Save each erosion step
      char filename[50];
      sprintf(filename, ".\\output_images\\OUTeroded%d.bmp", i);
      write_binary_bitmap(outputImagePtr, filename);

      capture(outputImagePtr, &result);
      printf("After erosion step %d, captured %d chords\n", i, result.n);
      
      // Swap temp1 and temp2 pointers
      unsigned char (*tmp)[BMP_HEIGTH] = outputImagePtr;
      outputImagePtr = inputImagePtr;
      inputImagePtr = tmp;

      // Increment step counter
      i++;
  }
  printf("Captured %d chords:\n", result.n);

  return result;
}

//Declaring the array to store the image (unsigned char = unsigned 8 bit)
unsigned char input_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS];
unsigned char output_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS];

//Main function
int main(int argc, char** argv)
{
    if (argc < 3 || argc > 4)
    {
        fprintf(stderr, "Usage: %s <input file path> <output file path> [sigma]\n", argv[0]);
        exit(1);
    }

    double sigma = 1.0;
    if (argc == 4) sigma = atof(argv[3]);

    // Load image from file
    read_bitmap(argv[1], input_image);

    // Use two buffers and pointers for processing
    unsigned char buffer1[BMP_WIDTH][BMP_HEIGTH];
    unsigned char buffer2[BMP_WIDTH][BMP_HEIGTH];
    unsigned char (*current)[BMP_HEIGTH] = buffer1;
    unsigned char (*next)[BMP_HEIGTH] = buffer2;

    // Step 1: Grayscale
    toGrayScale(input_image, current);
    write_grayScale_bitmap(current, ".\\output_images\\OUTgrayscale.bmp");

    // Step 1.5: Blur (background subtraction)
    bgSubtractGaussian(current, next, sigma);
    unsigned char (*tmp)[BMP_HEIGTH] = current;
    current = next;
    next = tmp;
    write_grayScale_bitmap(current, ".\\output_images\\OUTblurred.bmp");

    // Step 2: Binary Threshold
    toBinaryScale(current);
    write_binary_bitmap(current, ".\\output_images\\OutBinary.bmp");

    // Step 3 & 4: Erode and Capture
    struct CaptureResult result = erodeAndCaptureAll(current);

    // Step 5: Marking Cells with X
    drawAllX(input_image, result.chords, result.n);

    // Step 6: Save the final image with marked cells
    write_bitmap(input_image, argv[2]);

    printf("Done!\n");
    return 0;
}
