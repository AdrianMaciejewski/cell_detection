#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "cbmp.h"
#include "Step1GrayScale.h"
#include "Step2BinaryThreshold.h"
#include "Step3Erode.h"
#include "Step4Capture.h"
#include "Step5MarkingCells.h"

struct ProcessingResults {
    unsigned char original[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS];
    unsigned char grayscale[BMP_WIDTH][BMP_HEIGTH];
    unsigned char binary[BMP_WIDTH][BMP_HEIGTH];
    unsigned char marked[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS];
    int chords[10000][2];
    int nChords;
};

void copyResults(
    struct ProcessingResults* results,
    unsigned char original[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS],
    unsigned char grayscale[BMP_WIDTH][BMP_HEIGTH],
    unsigned char binary[BMP_WIDTH][BMP_HEIGTH],
    unsigned char marked[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS],
    int chords[][2],
    int nChords
) {
    memcpy(results->original, original, sizeof(results->original));
    memcpy(results->grayscale, grayscale, sizeof(results->grayscale));
    memcpy(results->binary, binary, sizeof(results->binary));
    memcpy(results->marked, marked, sizeof(results->marked));
    memcpy(results->chords, chords, sizeof(int) * 2 * nChords);
    results->nChords = nChords;
}

void save_results_as_c_initializer(const char* filename, struct ProcessingResults* results) {
    FILE* f = fopen(filename, "w");
    if (!f) {
        fprintf(stderr, "Could not open %s for writing\n", filename);
        return;
    }

    // Original
    fprintf(f, "unsigned char original[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS] = {\n");
    for (int i = 0; i < BMP_WIDTH; i++) {
        fprintf(f, "    {\n");
        for (int j = 0; j < BMP_HEIGTH; j++) {
            fprintf(f, "        {%u, %u, %u}", 
                results->original[i][j][0], 
                results->original[i][j][1], 
                results->original[i][j][2]);
            if (j < BMP_HEIGTH - 1) fprintf(f, ", ");
        }
        fprintf(f, "    }%s\n", (i < BMP_WIDTH - 1) ? "," : "");
    }
    fprintf(f, "};\n\n");

    // Grayscale
    fprintf(f, "unsigned char grayscale[BMP_WIDTH][BMP_HEIGTH] = {\n");
    for (int i = 0; i < BMP_WIDTH; i++) {
        fprintf(f, "    {");
        for (int j = 0; j < BMP_HEIGTH; j++) {
            fprintf(f, "%u", results->grayscale[i][j]);
            if (j < BMP_HEIGTH - 1) fprintf(f, ", ");
        }
        fprintf(f, "}%s\n", (i < BMP_WIDTH - 1) ? "," : "");
    }
    fprintf(f, "};\n\n");

    // Binary
    fprintf(f, "unsigned char binary[BMP_WIDTH][BMP_HEIGTH] = {\n");
    for (int i = 0; i < BMP_WIDTH; i++) {
        fprintf(f, "    {");
        for (int j = 0; j < BMP_HEIGTH; j++) {
            fprintf(f, "%u", results->binary[i][j]);
            if (j < BMP_HEIGTH - 1) fprintf(f, ", ");
        }
        fprintf(f, "}%s\n", (i < BMP_WIDTH - 1) ? "," : "");
    }
    fprintf(f, "};\n\n");

    // Marked image
    fprintf(f, "unsigned char marked[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS] = {\n");
    for (int i = 0; i < BMP_WIDTH; i++) {
        fprintf(f, "    {\n");
        for (int j = 0; j < BMP_HEIGTH; j++) {
            fprintf(f, "        {%u, %u, %u}", 
                results->marked[i][j][0], 
                results->marked[i][j][1], 
                results->marked[i][j][2]);
            if (j < BMP_HEIGTH - 1) fprintf(f, ", ");
        }
        fprintf(f, "    }%s\n", (i < BMP_WIDTH - 1) ? "," : "");
    }
    fprintf(f, "};\n\n");

    // Chords
    fprintf(f, "int chords[%d][2] = {\n", results->nChords);
    for (int i = 0; i < results->nChords; i++) {
        fprintf(f, "    {%d, %d}", results->chords[i][0], results->chords[i][1]);
        if (i < results->nChords - 1) fprintf(f, ",\n");
        else fprintf(f, "\n");
    }
    fprintf(f, "};\n");
    fprintf(f, "int nChords = %d;\n", results->nChords);

    fclose(f);
}

//Declaring the array to store the image (unsigned char = unsigned 8 bit)
unsigned char input_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS];
unsigned char output_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS];
struct ProcessingResults results;

//Main function
int main(int argc, char** argv)
{
  if (argc != 3)
  {
      fprintf(stderr, "Usage: %s <output file path> <output file path>\n", argv[0]);
      exit(1);
  }

  //Load image from file
  read_bitmap(argv[1], input_image);
  memcpy(results.original, input_image, sizeof(input_image));

  unsigned char processedImage[BMP_WIDTH][BMP_HEIGTH];

  // Step 1: Grayscale
  toGrayScale(input_image, processedImage);
  memcpy(results.grayscale, processedImage, sizeof(processedImage));

  // Step 2: Binary Threshold
  toBinaryScale(processedImage);
  memcpy(results.binary, processedImage, sizeof(processedImage));

  // Step 3 & 4: Erode and Capture
  struct CaptureResult result = erodeAndCaptureAll(processedImage);
  memcpy(results.chords, result.chords, sizeof(result.chords));
  results.nChords = result.n;

  // Step 5: Marking Cells with X
  drawAllX(input_image, result.chords, result.n);
  memcpy(results.marked, input_image, sizeof(input_image));

  save_results_as_c_initializer(".\\tests\\TestData.c", &results);
  printf("Done!\n");
  return 0;
}