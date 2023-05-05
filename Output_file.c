//
// Created by kikig on 4.5.2023 г..
//
#include "structs.h"
#include <stdlib.h>
#include <stdio.h>

void invert_1bits(BMP *bmp, DIB *dib, PIXEL_1 *pixels, FILE *f, FILE *f1) {
    fseek(f1, (*bmp).dataoffset, SEEK_SET);
    int x = 0;
    while (x < (*dib).width) {
        int y = 0;
        while (y < (*dib).height) {

            unsigned int color = pixels[x * (*dib).width + y].color;
            color = ~color;
            pixels[x * (*dib).width + y].color = (char) color;
            //  printf("Pixel 1 is %d\n", pixel.b);



            fwrite(&pixels[x * (*dib).width + y].color, 1, 1, f1);
            y += 8;
            fseek(f1, 0, SEEK_CUR);


        }
        fseek(f1, 0, SEEK_CUR);

        x += 1;
    }
}

void invert_2bits(BMP *bmp, DIB *dib, PIXEL_2 *pixels, FILE *f, FILE *f1) {
    fseek(f1, (*bmp).dataoffset, SEEK_SET);

    int x = 0;
    while (x < (*dib).width) {
        int y = 0;
        while (y < (*dib).height) {

            unsigned int color = pixels[x * (*dib).width + y].color;
            color = ~color;
            pixels[x * (*dib).width + y].color = (char) color;
            //  printf("Pixel 1 is %d\n", pixel.b);



            fwrite(&pixels[x * (*dib).width + y].color, 1, 1, f1);
            fseek(f1, 0, SEEK_CUR);

            y += 4;
        }
        fseek(f1, 0, SEEK_CUR);

        x += 1;
    }
}

void flip_4bits(BMP *bmp, DIB *dib, PIXEL_4 *pixels, FILE *f, FILE *f1) {
    fseek(f1, (*bmp).dataoffset, SEEK_SET);
    int pixelSize = (*dib).height * (*dib).width;
    PIXEL_4 *pixels_2 = malloc(dib->width * dib->height * sizeof(PIXEL_4));
    PIXEL_4 *pixels_3 = malloc(dib->width * dib->height * sizeof(PIXEL_4));
    for (int i = 0; i < pixelSize - 1; i += 2) {
        // color
        unsigned char c = pixels[i].color;
        unsigned char c1 = c >> 4;
        c = c << 4;
        unsigned char c2 = c >> 4;
        pixels_2[i].color = c1;
        pixels_2[i + 1].color = c2;

    }
    for (int x = 0; x < (*dib).width; x++) {
        int x1 = (*dib).height - 1;

        for (int y = 0; y < (*dib).height; y += 1) {

            pixels_3[x * (*dib).width + y].color = pixels_2[x * (*dib).width + x1].color;
            x1 -= 1;
        }

    }
    fseek(f1, (*bmp).dataoffset, SEEK_SET);
    int x = 0;
    while (x < (*dib).width) {
        int y = 0;
        while (y < (*dib).height) {
            unsigned char result = 0;
            result += pixels_3[x * (*dib).width + y].color;
            result = result << 4;
            result += pixels_3[x * (*dib).width + y + 1].color;
            fwrite(&result, 1, 1, f1);
            y += 2;
            fseek(f1, 0, SEEK_CUR);

        }

        fseek(f1, 0, SEEK_CUR);
        x++;
    }
}

void rotate_4bits(BMP *bmp, DIB *dib, PIXEL_4 *pixels, FILE *f, FILE *f1) {
    fseek(f1, (*bmp).dataoffset, SEEK_SET);
    int pixelSize = (*dib).height * (*dib).width;
    PIXEL_4 *pixels_2 = malloc(dib->width * dib->height * sizeof(PIXEL_4));
    PIXEL_4 *pixels_3 = malloc(dib->width * dib->height * sizeof(PIXEL_4));
    for (int i = 0; i < pixelSize - 1; i += 2) {
        // color
        unsigned char c = pixels[i].color;
        unsigned char c1 = c >> 4;
        c = c << 4;
        unsigned char c2 = c >> 4;
        pixels_2[i].color = c1;
        pixels_2[i + 1].color = c2;
        pixels_3[i].color = c1;
        pixels_3[i + 1].color = c2;


    }
    int x1 = (*dib).width - 1;
    for (int i = 0; i < (*dib).width; i++) {
        for (int y = 0; y < (*dib).height; y += 1) {
            pixels_2[y * (*dib).width + x1].color = pixels_3[i * (*dib).width + y].color;
        }
        x1 -= 1;
    }
    fseek(f1, (*bmp).dataoffset, SEEK_SET);
    int x = 0;
    while (x < (*dib).width) {
        int y = 0;
        while (y < (*dib).height) {
            unsigned char result = 0;
            result += pixels_2[x * (*dib).width + y].color;
            result = result << 4;
            result += pixels_2[x * (*dib).width + y + 1].color;
            fwrite(&result, 1, 1, f1);
            y += 2;
            fseek(f1, 0, SEEK_CUR);

        }

        fseek(f1, 0, SEEK_CUR);
        x++;
    }
}

void invert_4bits(BMP *bmp, DIB *dib, PIXEL_4 *pixels, FILE *f, FILE *f1) {
    fseek(f1, (*bmp).dataoffset, SEEK_SET);

    int x = 0;
    while (x < (*dib).width) {
        int y = 0;
        while (y < (*dib).height) {

            unsigned int color = pixels[x * (*dib).width + y].color;
            color = ~color;
            pixels[x * (*dib).width + y].color = (char) color;


            fwrite(&pixels[x * (*dib).width + y].color, 1, 1, f1);
            fseek(f1, 0, SEEK_CUR);

            y += 2;
        }
        fseek(f1, 0, SEEK_CUR);

        x += 1;
    }
}

void flip_8bits(BMP *bmp, DIB *dib, PIXEL_8 *pixels, FILE *f, FILE *f1) {
    fseek(f1, (*bmp).dataoffset, SEEK_SET);
    PIXEL_8 *pixels_2 = malloc(dib->width * dib->height * sizeof(PIXEL_8));
    for (int x = 0; x < (*dib).width; x++) {
        int x1 = (*dib).height - 1;

        for (int y = 0; y < (*dib).height; y++) {

            pixels_2[x * (*dib).width + y].color = pixels[x * (*dib).width + x1].color;
            x1--;
        }

    }
    fseek(f1, (*bmp).dataoffset, SEEK_SET);

    int x = 0;
    while (x < (*dib).width) {
        int y = 0;
        while (y < (*dib).height) {
            fwrite(&pixels_2[x * (*dib).width + y].color, 1, 1, f1);
            y++;
            fseek(f1, 0, SEEK_CUR);

        }

        fseek(f1, 0, SEEK_CUR);
        x++;
    }
}

void rotate_8bits(BMP *bmp, DIB *dib, PIXEL_8 *pixels, FILE *f, FILE *f1) {
    fseek(f1, (*bmp).dataoffset, SEEK_SET);
    PIXEL_8 *pixels_2 = malloc(dib->width * dib->height * sizeof(PIXEL_8));
    int x1 = (*dib).width - 1;
    for (int i = 0; i < (*dib).width; i++) {
        for (int y = 0; y < (*dib).height; y++) {
            pixels_2[y * (*dib).width + x1].color = pixels[i * (*dib).width + y].color;
        }
        x1--;
    }
    fseek(f1, (*bmp).dataoffset, SEEK_SET);
    int x = 0;
    while (x < (*dib).width) {
        int y = 0;
        while (y < (*dib).height) {
            fwrite(&pixels_2[x * (*dib).width + y].color, 1, 1, f1);
            y++;
            fseek(f1, 0, SEEK_CUR);

        }

        fseek(f1, 0, SEEK_CUR);
        x++;
    }
}

void invert_8bits(BMP *bmp, DIB *dib, PIXEL_8 *pixels, FILE *f, FILE *f1) {
    fseek(f1, (*bmp).dataoffset, SEEK_SET);

    int x = 0;
    while (x < (*dib).width) {
        int y = 0;
        while (y < (*dib).height) {

            unsigned int color = pixels[x * (*dib).width + y].color;
            color = ~color;
            pixels[x * (*dib).width + y].color = (char) color;


            fwrite(&pixels[x * (*dib).width + y].color, 1, 1, f1);
            fseek(f1, 0, SEEK_CUR);

            y++;
        }
        fseek(f1, 0, SEEK_CUR);

        x++;
    }
}

void flip_16bits(BMP *bmp, DIB *dib, PIXEL_16 *pixels, FILE *f, FILE *f1) {
    fseek(f1, (*bmp).dataoffset, SEEK_SET);
    PIXEL_16 *pixels_2 = malloc(dib->width * dib->height * sizeof(PIXEL_16));
    for (int x = 0; x < (*dib).width; x++) {
        int x1 = (*dib).height - 1;

        for (int y = 0; y < (*dib).height; y++) {

            pixels_2[x * (*dib).width + y].a_r = pixels[x * (*dib).width + x1].a_r;
            pixels_2[x * (*dib).width + y].b_g = pixels[x * (*dib).width + x1].b_g;
            x1--;
        }

    }
    fseek(f1, (*bmp).dataoffset, SEEK_SET);

    int x = 0;
    while (x < (*dib).width) {
        int y = 0;
        while (y < (*dib).height) {
            fwrite(&pixels_2[x * (*dib).width + y].b_g, 1, 1, f1);
            fwrite(&pixels_2[x * (*dib).width + y].a_r, 1, 1, f1);
            y++;
            fseek(f1, 0, SEEK_CUR);

        }

        fseek(f1, 0, SEEK_CUR);
        x++;
    }
}

void rotate_16bits(BMP *bmp, DIB *dib, PIXEL_16 *pixels, FILE *f, FILE *f1) {
    fseek(f1, (*bmp).dataoffset, SEEK_SET);
    PIXEL_16 *pixels_2 = malloc(dib->width * dib->height * sizeof(PIXEL_16));
    int x1 = (*dib).width - 1;
    for (int i = 0; i < (*dib).width; i++) {
        for (int y = 0; y < (*dib).height; y++) {
            pixels_2[y * (*dib).width + x1].a_r = pixels[i * (*dib).width + y].a_r;
            pixels_2[y * (*dib).width + x1].b_g = pixels[i * (*dib).width + y].b_g;
        }
        x1--;
    }
    fseek(f1, (*bmp).dataoffset, SEEK_SET);

    int x = 0;
    while (x < (*dib).width) {
        int y = 0;
        while (y < (*dib).height) {
            fwrite(&pixels_2[x * (*dib).width + y].b_g, 1, 1, f1);
            fwrite(&pixels_2[x * (*dib).width + y].a_r, 1, 1, f1);
            y++;
            fseek(f1, 0, SEEK_CUR);

        }

        fseek(f1, 0, SEEK_CUR);
        x++;
    }
}

void invert_16bits(BMP *bmp, DIB *dib, PIXEL_16 *pixels, FILE *f, FILE *f1) {
    fseek(f1, (*bmp).dataoffset, SEEK_SET);

    int x = 0;
    while (x < (*dib).width) {
        int y = 0;
        while (y < (*dib).height) {


            unsigned int blue = pixels[x * (*dib).width + y].b_g;
            blue = ~blue;
            pixels[x * (*dib).width + y].b_g = (char) blue;

            unsigned int green = pixels[x * (*dib).width + y].a_r;
            green = ~green;
            pixels[x * (*dib).width + y].a_r = (char) green;


            fwrite(&pixels[x * (*dib).width + y].b_g, 1, 1, f1);
            fwrite(&pixels[x * (*dib).width + y].a_r, 1, 1, f1);
            fseek(f1, 0, SEEK_CUR);

            y++;
        }
        fseek(f1, 0, SEEK_CUR);

        x++;
    }
}

void flip_24bits(BMP *bmp, DIB *dib, PIXEL_24 *pixels, FILE *f, FILE *f1) {
    PIXEL_24 *pixels_2 = malloc(dib->width * dib->height * sizeof(PIXEL_24));
    for (int x = 0; x < (*dib).width; x++) {
        int x1 = (*dib).height - 1;

        for (int y = 0; y < (*dib).height; y++) {

            pixels_2[x * (*dib).width + y].b = pixels[x * (*dib).width + x1].b;
            pixels_2[x * (*dib).width + y].g = pixels[x * (*dib).width + x1].g;
            pixels_2[x * (*dib).width + y].r = pixels[x * (*dib).width + x1].r;
            x1--;
        }

    }
    fseek(f1, (*bmp).dataoffset, SEEK_SET);

    int x = 0;
    while (x < (*dib).width) {
        int y = 0;
        while (y < (*dib).height) {
            fwrite(&pixels_2[x * (*dib).width + y], 1, 1, f1);
            fwrite(&pixels_2[x * (*dib).width + y], 1, 1, f1);
            fwrite(&pixels_2[x * (*dib).width + y], 1, 1, f1);
            y++;
            fseek(f1, 0, SEEK_CUR);

        }

        fseek(f1, 0, SEEK_CUR);
        x++;
    }
}

void rotate_24bits(BMP *bmp, DIB *dib, PIXEL_24 *pixels, FILE *f, FILE *f1) {
    PIXEL_24 *pixels_2 = malloc(dib->width * dib->height * sizeof(PIXEL_24));
    int x1 = (*dib).width - 1;
    for (int i = 0; i < (*dib).width; i++) {
        for (int y = 0; y < (*dib).height; y++) {
            pixels_2[y * (*dib).width + x1].b = pixels[i * (*dib).width + y].b;
            pixels_2[y * (*dib).width + x1].g = pixels[i * (*dib).width + y].g;
            pixels_2[y * (*dib).width + x1].r = pixels[i * (*dib).width + y].r;
        }
        x1--;
    }
    fseek(f1, (*bmp).dataoffset, SEEK_SET);

    int x = 0;
    while (x < (*dib).width) {
        int y = 0;
        while (y < (*dib).height) {
            fwrite(&pixels_2[x * (*dib).width + y].b, 1, 1, f1);
            fwrite(&pixels_2[x * (*dib).width + y].g, 1, 1, f1);
            fwrite(&pixels_2[x * (*dib).width + y].r, 1, 1, f1);
            y++;
            fseek(f1, 0, SEEK_CUR);

        }

        fseek(f1, 0, SEEK_CUR);
        x++;
    }
}

void invert_24bits(BMP *bmp, DIB *dib, PIXEL_24 *pixels, FILE *f, FILE *f1) {
    fseek(f1, bmp->dataoffset, SEEK_SET);

    int x = 0;
    while (x < (*dib).width) {
        int y = 0;
        while (y < (*dib).height) {

            unsigned int blue = pixels[x * dib->width + y].b;
            blue = ~blue;
            pixels[x * dib->width + y].b = (char) blue;

            unsigned int green = pixels[x * dib->width + y].g;
            green = ~green;
            pixels[x * dib->width + y].g = (char) green;

            unsigned int red = pixels[x * dib->width + y].r;
            red = ~red;
            pixels[x * dib->width + y].r = (char) red;

            fwrite(&pixels[x * dib->width + y].b, 1, 1, f1);
            fwrite(&pixels[x * dib->width + y].g, 1, 1, f1);
            fwrite(&pixels[x * dib->width + y].r, 1, 1, f1);
            fseek(f1, 0, SEEK_CUR);

            y++;
        }
        fseek(f1, 0, SEEK_CUR);

        x++;
    }
}

void copy_file(FILE *f, FILE *f1) {
    size_t n, m;
    unsigned char buff[8192];
    do {
        n = fread(buff, 1, sizeof buff, f);
        if (n) m = fwrite(buff, 1, n, f1);
        else m = 0;
    } while ((n > 0) && (n == m));
    if (m) perror("copy");
}