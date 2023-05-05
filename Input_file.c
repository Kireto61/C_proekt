//
// Created by kikig on 4.5.2023 г..
//
#include "structs.h"
#include <stdlib.h>
#include <stdio.h>

void input_bmp_Dib(FILE *f, struct BMP *bmp, struct DIB *dib) {
    fread(&(*bmp).filetype, 1, 2, f);


    if ((*bmp).filetype[0] != 'B' && (*bmp).filetype[1] != 'M') {
        printf("Greshen format");
        exit(1);
    }


    fread(&(*bmp).filesize, 4, 1, f);
    printf("Value is %d\n", (*bmp).filesize);

    fseek(f, 4, SEEK_CUR);

    fread(&(*bmp).dataoffset, 4, 1, f);
    printf("Offset is %d\n", (*bmp).dataoffset);


    //   fwrite(&bmp, sizeof(bmp), 1, f1);


    fread(&(*dib).fileheader, 4, 1, f);
    printf("File header is %d bytes\n", (*dib).fileheader);

    //if (dib.fileheader != 40) {
//    printf("Greshen format");
//   exit(-1);
//}

    fread(&(*dib).width, 4, 1, f);
    printf("Width is %d\n", (*dib).width);

    fread(&(*dib).height, 4, 1, f);
    printf("Height is %d\n", (*dib).height);

    fread(&(*dib).planes, 2, 1, f);
    printf("Color planes is %d\n", (*dib).planes);


    fread(&(*dib).bitsperpixel, 2, 1, f);
    printf("Pixels per bit is %d\n", (*dib).bitsperpixel);

    fread(&(*dib).compression, 4, 1, f);
    printf("Compression scheme used is %d\n", (*dib).compression);

    fread(&(*dib).bitmapsize, 4, 1, f);
    printf("Image size is %d\n", (*dib).bitmapsize);

    fread(&(*dib).horizontalres, 4, 1, f);
    printf("Horizontal resolution is %d\n", (*dib).horizontalres);

    fread(&(*dib).verticalres, 4, 1, f);
    printf("Vertical resolution is %d\n", (*dib).verticalres);

    fread(&(*dib).numcolors, 4, 1, f);
    printf("Number of colors used %d\n", (*dib).numcolors);

    fread(&(*dib).importantcolors, 4, 1, f);
    printf("Important colors used %d\n", (*dib).importantcolors);
}

void read_pixel_24bit(FILE *f, struct BMP *bmp, struct DIB *dib, PIXEL_24 *pixels) {
    fseek(f, (*bmp).dataoffset, SEEK_SET);

    int pixelSize = (*dib).height * (*dib).width;
    for (int i = 0; i < pixelSize; i += 1) {
        // Blue
        fread(&pixels[i].b, 1, 1, f);
        // Green
        fread(&pixels[i].g, 1, 1, f);
        // Red
        fread(&pixels[i].r, 1, 1, f);
    }
}

void read_pixel_16bit(FILE *f1, struct BMP *bmp, struct DIB *dib, PIXEL_16 *pixels) {
    fseek(f1, (*bmp).dataoffset, SEEK_SET);

    int pixelSize = (*dib).height * (*dib).width;
    for (int i = 0; i < pixelSize; i += 1) {
        // Blue
        fread(&pixels[i].b_g, 1, 1, f1);
        // Green
        fread(&pixels[i].a_r, 1, 1, f1);
    }
}

void read_pixel_8bit(FILE *f1, struct BMP *bmp, struct DIB *dib, PIXEL_8 *pixels) {
    fseek(f1, (*bmp).dataoffset, SEEK_SET);

    int pixelSize = (*dib).height * (*dib).width;
    for (int i = 0; i < pixelSize; i += 1) {
        // color
        fread(&pixels[i].color, 1, 1, f1);
    }
}

void read_pixel_4bit(FILE *f1, struct BMP *bmp, struct DIB *dib, PIXEL_4 *pixels) {
    fseek(f1, (*bmp).dataoffset, SEEK_SET);
    int pixelSize = (*dib).height * (*dib).width;
    for (int i = 0; i < pixelSize - 1; i += 2) {
        fread(&pixels[i].color, 1, 1, f1);
    }
}

void read_pixel_2bit(FILE *f1, struct BMP *bmp, struct DIB *dib, PIXEL_2 *pixels) {
    fseek(f1, (*bmp).dataoffset, SEEK_SET);
    int pixelSize = (*dib).height * (*dib).width;
    for (int i = 0; i < pixelSize - 1; i += 4) {
        fread(&pixels[i].color, 1, 1, f1);
    }
}

void read_pixel_1bit(FILE *f1, struct BMP *bmp, struct DIB *dib, PIXEL_1 *pixels) {
    fseek(f1, (*bmp).dataoffset, SEEK_SET);
    int pixelSize = (*dib).height * (*dib).width;
    for (int i = 0; i < pixelSize - 1; i += 8) {
        fread(&pixels[i].color, 1, 1, f1);
    }
}

