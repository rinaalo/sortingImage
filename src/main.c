#include <stdio.h>
#include <stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define IMAGE "img/nisa.jpg"
#define OUTPUT_IMAGE "output/nisa"
//#define IMAGE "img/otter.png"
//#define OUTPUT_IMAGE "output/otter"

typedef unsigned char u8;

typedef struct {
    u8 R;
    u8 B;
    u8 G;
} Color;

float luminance_of_pixel(Color pixel) {
    // luminance formula: https://en.wikipedia.org/wiki/Relative_luminance
    return pixel.R + pixel.G + pixel.B;
    // return 0.2126*pixel.R + 0.7152*pixel.G + 0.0722*pixel.B;
}

void sort_column_by_luminance(Color *column, int length) {
    // assuming row major
    // using insertion sort
    for (int i = 1; i < length; i++) {
        Color x = column[i];
        int j = i - 1;
        while (j >= 0 && luminance_of_pixel(column[j]) > luminance_of_pixel(x)) {
            column[j + 1] = column[j];
            j--;
        }
        column[j + 1] = x;
    }
}

int main() {
    int width, height, channels;
    Color *img = (Color*)stbi_load(IMAGE, &width, &height, &channels, 0);
    if (img == NULL) {
        fprintf(stderr,"Error loading the image\n");
        exit(1);
    }

    Color *column_buffer = malloc(height * sizeof(Color));
    for (int column = 0; column < width; column++) {
        for (int row = 0; row < height; row++) {
            column_buffer[row] = img[column + row * width];
        }
        sort_column_by_luminance(column_buffer, height);
        for (int row = 0; row < height; row++) {
            img[column + row * width] = column_buffer[row];
        }
    }
    free(column_buffer);
    // create new image out of image buffer
    //int aa = stbi_write_jpg(OUTPUT_IMAGE, width, height, channels, img, 100);
    if (!stbi_write_jpg(OUTPUT_IMAGE ".jpg", width, height, channels, img, 100)) {
        fprintf(stderr, "Could not create image %s.jpg", OUTPUT_IMAGE);
    }
    if (!stbi_write_bmp(OUTPUT_IMAGE ".bmp", width, height, channels, img)) {
        fprintf(stderr, "Could not create image %s.bmp", OUTPUT_IMAGE);
    }
    if (!stbi_write_png(OUTPUT_IMAGE ".png", width, height, channels, img, width * channels)) {
        fprintf(stderr, "Could not create image %s.png", OUTPUT_IMAGE);
    }
    stbi_image_free(img);
    return 0;
}