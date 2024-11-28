#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Utilities/image.h"
#include "Utilities/rlog.h"

#define W 800
#define H 600

int main(void) {
  Color** pixels = malloc(sizeof(Color) * H);
  for (int y = 0; y < H; y++) {
    pixels[y] = malloc(sizeof(Color) * W);
    for (int x = 0; x < W; x++) {
      pixels[y][x] = (Color){1.0f - ((float)x/W), 0.5f, 1.0f - ((float)y/H)};
    }
  }

  clock_t start_time = clock();

  if (write_image(FORMAT_JPG, W, H, pixels) != 0) {
    rlog(WARNING, "Something failed");
    return -1;
  }

  clock_t end_time = clock();

  rlog(INFO, "Program finished in %.6f seconds", (double)(end_time-start_time)/CLOCKS_PER_SEC);

  for (unsigned int y = 0; y < H; y++) 
    free(pixels[y]);
  free(pixels);

  return 0;
}
