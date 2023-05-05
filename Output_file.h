//
// Created by kikig on 4.5.2023 г..
//

#ifndef UNTITLED_OUTPUT_FILE_H
#define UNTITLED_OUTPUT_FILE_H


#include <stdio.h>
#include "structs.h"

void copy_file(FILE *f, FILE *f1);

void flip_1bits(BMP *bmp, DIB *dib, PIXEL_1 *pixels, FILE *f, FILE *f1);

void rotate_1bits(BMP *bmp, DIB *dib, PIXEL_1 *pixels, FILE *f, FILE *f1);

void invert_1bits(BMP *bmp, DIB *dib, PIXEL_1 *pixels, FILE *f, FILE *f1);

void flip_2bits(BMP *bmp, DIB *dib, PIXEL_2 *pixels, FILE *f, FILE *f1);

void rotate_2bits(BMP *bmp, DIB *dib, PIXEL_2 *pixels, FILE *f, FILE *f1);

void invert_2bits(BMP *bmp, DIB *dib, PIXEL_2 *pixels, FILE *f, FILE *f1);

void flip_4bits(BMP *bmp, DIB *dib, PIXEL_4 *pixels, FILE *f, FILE *f1);

void rotate_4bits(BMP *bmp, DIB *dib, PIXEL_4 *pixels, FILE *f, FILE *f1);

void invert_4bits(BMP *bmp, DIB *dib, PIXEL_4 *pixels, FILE *f, FILE *f1);

void flip_8bits(BMP *bmp, DIB *dib, PIXEL_8 *pixels, FILE *f, FILE *f1);

void rotate_8bits(BMP *bmp, DIB *dib, PIXEL_8 *pixels, FILE *f, FILE *f1);

void invert_8bits(BMP *bmp, DIB *dib, PIXEL_8 *pixels, FILE *f, FILE *f1);

void flip_16bits(BMP *bmp, DIB *dib, PIXEL_16 *pixels, FILE *f, FILE *f1);

void rotate_16bits(BMP *bmp, DIB *dib, PIXEL_16 *pixels, FILE *f, FILE *f1);

void invert_16bits(BMP *bmp, DIB *dib, PIXEL_16 *pixels, FILE *f, FILE *f1);

void flip_24bits(BMP *bmp, DIB *dib, PIXEL_24 *pixels, FILE *f, FILE *f1);

void rotate_24bits(BMP *bmp, DIB *dib, PIXEL_24 *pixels, FILE *f, FILE *f1);

void invert_24bits(BMP *bmp, DIB *dib, PIXEL_24 *pixels, FILE *f, FILE *f1);

#endif //UNTITLED_OUTPUT_FILE_H
