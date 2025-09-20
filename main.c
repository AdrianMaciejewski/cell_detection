//To compile (linux/mac): gcc cbmp.c main.c -o main.out -std=c99
//To run (linux/mac): ./main.out example.bmp example_inv.bmp

//To compile (win): gcc cbmp.c main.c -o main.exe -std=c99
//To run (win): main.exe example.bmp example_inv.bmp

#include <stdlib.h>
#include <stdio.h>
#include "cbmp.h"
#include "Step1GrayScale.h"
#include "Step2BinaryThreshold.h"
#include "Step3Erode.h"


//Main function
int main(int argc, char** argv)
{
  if (argc != 3)
  {
      fprintf(stderr, "Usage: %s <output file path> <output file path>\n", argv[0]);
      exit(1);
  }
  
  printf("SEAL! 🦭");

  //Declaring the array to store the image (unsigned char = unsigned 8 bit)
  unsigned char input_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS];
  unsigned char output_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS];

  //Load image from file
  read_bitmap(argv[1], input_image);

  unsigned char temp1[BMP_WIDTH][BMP_HEIGTH];
  unsigned char (*temp1Ptr)[BMP_HEIGTH] = temp1;
  unsigned char temp2[BMP_WIDTH][BMP_HEIGTH];
  unsigned char (*temp2Ptr)[BMP_HEIGTH] = temp2;

  // Step 1: Grayscale
  toGrayScale(input_image, temp1);
  write_grayScale_bitmap(temp1, "OUTgrayscale.bmp");

  // Step 2: Binary Threshold
  toBinaryScale(temp1);
  write_binary_bitmap(temp1, "OutBinary.bmp");

  // Step 3: Erode until fully eroded
  int i=0;
  while (!erode(temp1Ptr, temp2Ptr)) {
      // Save each erosion step
      char filename[20];
      sprintf(filename, "OUTeroded%d.bmp", i);
      write_binary_bitmap(temp2Ptr, filename);
      
      // Swap temp1 and temp2 pointers
      unsigned char (*tmp)[BMP_HEIGTH] = temp1Ptr;
      temp1Ptr = temp2Ptr;
      temp2Ptr = tmp;

      // Increment step counter
      i++;
  }

  printf("Done!\n");
  return 0;
}
