#pragma once
// THIS IS USED WHEN COMPILED WITH 'IMAGE'

typedef enum {
  FORMAT_PPM,
  FORMAT_JPG
} ImageFormat;

typedef struct {
  float r;
  float g;
  float b;
} Color;

/*
 * write_image creates a new image of size wxh with the specified format and fills it with the specified pixel data
 *
 * Input:
 *  ImageFormat format: the file format of the image (currently supports only PPM)
 *  unsigned int w: the width of the image
 *  unsigned int h: the height of the image
 *  Color** pixel_data: the color values of each pixel
 *
 * Output:
 *  Returns 0 on success, in the future will return meaningful codes otherwise
 */
int write_image(ImageFormat format, unsigned int w, unsigned int h, Color** pixel_data);
