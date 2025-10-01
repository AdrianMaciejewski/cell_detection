#include <stdlib.h>
#include <stdio.h>
#include "cbmp.h"
#include "Step1GrayScale.h"
#include "Step2BinaryThreshold.h"
#include "Step3Erode.h"
#include "Step4Capture.h"
#include "Step5MarkingCells.h"
#include "CellDetection.h"
#include "Debug.h"


//Declaring the array to store the image (unsigned char = unsigned 8 bit)
unsigned char input_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS];
unsigned char output_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS];

//Main function
int main(int argc, char** argv)
{
  if (argc <3 || argc > 5)
  {
      fprintf(stderr, "Usage: %s <output file path> <output file path>\n", argv[0]);
      printf("Optional flags:\n");
      printf(" --debug : Enable debug output e.g. printing and saving intermediary result images\n");
      printf(" --generate_test_data : Generate test data file TestData.c\n");
      exit(1);
  }
  for (int i = 1; i < argc; i++) {
      if (strcmp(argv[i], "--debug") == 0) {
          g_debug = true;
      }
      if (strcmp(argv[i], "--generate_test_data") == 0) {
          g_generate_test_data = true;
      }
  }

  read_bitmap(argv[1], input_image);
  detectCells(input_image);  
  write_bitmap(input_image, argv[2]);

    printf("Done!\n");
    return 0;
}
