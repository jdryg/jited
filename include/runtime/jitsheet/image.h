#ifndef IMAGE_H
#define IMAGE_H

#include <stdint.h>

// NOTE: All images are RGBA for now
typedef struct image_t image_t;

image_t* imageCreate(uint32_t width, uint32_t height, const uint8_t* data);
void imageDestroy(image_t* img);
void imageGetSize(image_t* img, uint32_t* width, uint32_t* height);
const uint8_t* imageGetData(image_t* img);
void imageSetPixel(image_t* img, uint32_t x, uint32_t y, const uint8_t* colorRGBA);
void imageSetRect(image_t* img, uint32_t x, uint32_t y, uint32_t w, uint32_t h, const uint32_t* data);

#endif // IMAGE_H
