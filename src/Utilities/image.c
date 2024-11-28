#include "image.h"

#include <stdio.h>
#include <stdlib.h>
#include <jpeglib.h>
#include "rlog.h"

int write_image(ImageFormat format, unsigned int w, unsigned int h, Color** pixel_data) {
  if (format == FORMAT_PPM) {
    FILE* out = fopen("output.ppm", "w");
    if (!out) {
      rlog(ERROR, "Could not open output image 'output.ppm'. Aborting");
      return -1;
    }

    fprintf(out, "P3\n");
    fprintf(out, "%u %u\n", w, h);
    fprintf(out, "255\n");

    for (unsigned int y = 0; y < h; y++) {
      for (unsigned int x = 0; x < w; x++) {
        Color pixel = pixel_data[y][x];

        int r = (int)(pixel.r * 255.0f);
        int g = (int)(pixel.g * 255.0f);
        int b = (int)(pixel.b * 255.0f);

        r = (r < 0) ? 0 : (r > 255) ? 255 : r;
        g = (g < 0) ? 0 : (g > 255) ? 255 : g;
        b = (b < 0) ? 0 : (b > 255) ? 255 : b;

        fprintf(out, "%d %d %d", r, g, b);
      }
      fprintf(out, "\n");
    }

    fclose(out);
    return 0;
  }

  else if (format == FORMAT_JPG) {
    const char* filename = "output.jpg";
    
    struct jpeg_compress_struct cinfo;
    struct jpeg_error_mgr jerr;

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&cinfo);

    FILE* out = fopen(filename, "wb");
    if (!out) {
      rlog(ERROR, "Could not open output image 'output.jpg'. Aborting");
      return -1;
    }

    jpeg_stdio_dest(&cinfo, out);

    cinfo.image_width = w;
    cinfo.image_height = h;
    cinfo.input_components = 3;
    cinfo.in_color_space = JCS_RGB;

    jpeg_set_defaults(&cinfo);
    jpeg_set_quality(&cinfo, 90, TRUE);
    
    jpeg_start_compress(&cinfo, TRUE);

    JSAMPROW row_pointer[1];
    unsigned char* row = (unsigned char*)malloc(3 * w * sizeof(unsigned char));
    if (!row) {
      rlog(ERROR, "Allocation for JPEG row failed. Aborting");
      jpeg_destroy_compress(&cinfo);
      fclose(out);
      return -1;
    }

    while (cinfo.next_scanline < cinfo.image_height) {
      unsigned int y = cinfo.next_scanline;
      for (unsigned int x = 0; x < w; x++) {
        Color pixel = pixel_data[y][x];

        unsigned char r = (unsigned char)(pixel.r * 255.0f);
        unsigned char g = (unsigned char)(pixel.g * 255.0f);
        unsigned char b = (unsigned char)(pixel.b * 255.0f);

        r = (r > 255) ? 255 : r;
        g = (g > 255) ? 255 : g;
        b = (b > 255) ? 255 : b;

        row[x * 3 + 0] = r;
        row[x * 3 + 1] = g;
        row[x * 3 + 2] = b;
      }

      row_pointer[0] = row;
      jpeg_write_scanlines(&cinfo, row_pointer, 1);
    }

    free(row);
    jpeg_finish_compress(&cinfo);
    jpeg_destroy_compress(&cinfo);
    fclose(out);

    return 0;
  }

  else {
    rlog(WARNING, "Image format not supported. Not doing anything");
    return 1;
  }

  return 0;
}
