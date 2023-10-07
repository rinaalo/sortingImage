#include <stdio.h>
#include <stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define IMAGE "img/nisa.jpg"

typedef unsigned char u8;

typedef struct {
    u8 R;
    u8 B;
    u8 G;
} Color;

float luminance_of_pixel(u8 *pixel) {
    // assuming rgb order
    // luminance formula: https://en.wikipedia.org/wiki/Relative_luminance
    float R = pixel[0], G = pixel[1], B = pixel[2];
    return 0.2126*R + 0.7152*G + 0.0722*B;
}

void sort_column_by_luminance(u8 *pixel) {
    // assuming row major
}

int main() {
    int width, height, channels;
    u8 *img = stbi_load(IMAGE, &width, &height, &channels, 0);
    if (img == NULL) {
        printf("Error loading the image\n");
        exit(1);
    }
    printf("image w:%d h:%d ch:%d\n", width, height, channels);
    Color *col_img = (Color*) img; 

    // sort image
    Color *column_buffer = malloc(height);
    for (int column = 0; column < width; column++) {
        // copy column into buffer
        for (int row = 0; row < height; row++) {
            column_buffer[row] = col_img[column + row * width];
            //printf("r %X g %X b %X\n", column_buffer[row].R, column_buffer[row].B, column_buffer[row].G);
        }
        // sort buffer
        // copy buffer into column
    }
    free(column_buffer);
    stbi_image_free(img);
    // create new image out of image buffer

    // calculate brightness of given pixel
    // sorting algorithm
    // run it every column 
    // output resulting image
    return 0;
}