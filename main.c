//
// Created by Kiril Valkov on 26.04.23.
//


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Input_file.h"
#include "Output_file.h"


void flip_1bits1(struct BMP *bmp, struct DIB *dib, FILE *f);

void rotate_1bits1(struct BMP *bmp, struct DIB *dib, FILE *f);

int main() {
    struct BMP bmp;
    struct DIB dib;


    FILE *f;
    FILE *f1;

    f = fopen("1.bmp", "rb+");
    f1 = fopen("111.bmp", "wb+");

    if (f == NULL) {
        perror("Greshka s faila");
        exit(1);
    }
    if (f1 == NULL) {
        perror("Greshka s faila");
        exit(1);
    }
    copy_file(f, f1);

    fseek(f, 0, SEEK_SET);
    fseek(f1, 0, SEEK_SET);

    input_bmp_Dib(f, &bmp, &dib);
    // PIXEL_1 *pixels = malloc(dib.width * dib.height * sizeof(PIXEL_1));

    //  read_pixel_1bit(f,&bmp,&dib,pixels);

    // invert_24bits(&bmp,&dib,pixels,f,f1);

     flip_1bits1(&bmp,&dib,f);

    ///reshenie na rotate 24pix

    //   rotate_24bits(&bmp, &dib, f);

    ///revenie na flip 24pix;

    //   fllip_24bits(&bmp, &dib, f);
    //  fwrite(&dib, sizeof(dib), 1, f1);
    switch (dib.bitsperpixel) {
        case 1:
            break;
        case 2:
            break;
        case 4:
            break;
        case 8:

            break;
        case 16:
            break;
        case 24:
            break;
        default:
            printf("error");
            return 1;
    }
    unsigned char c = 168;
    for (int i = 7; i >= 0; i--) {
        printf("%d ", (c >> i) & 1);
    }
    printf("reddy");
    fclose(f);
    fclose(f1);

    return 0;
}

unsigned char reverse(unsigned char b) {
    b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
    b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
    b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
    return b;
}


void flip_1bits1(struct BMP *bmp, struct DIB *dib, FILE *f) {
    fseek(f, (*bmp).dataoffset, SEEK_SET);

    unsigned int pixelSize = (dib->width) * (dib->height);
    unsigned char pixelArraycolor[dib->width][(int) ceil(dib->height / 8.0)];
    unsigned char pixelArraycolor2[pixelSize];
    unsigned char pixelArraycolor3[pixelSize];
    unsigned char pixelArraycolor4[dib->width][(int) ceil(dib->height / 8.0)];
    unsigned char pading = (4 - ((int) ceil((dib->height / 8.0))) % 4) % 4;
    unsigned char pading2 = (8 - ((dib->height) % 8)) % 8;
    printf("%d", pading2);
    for (int i = 0; i < dib->width; i++) {
        unsigned char d = 0;
        for (int j = 0; j < (int) ceil(dib->height / 8.0); j++) {
            fread(&d, 1, 1, f);
            pixelArraycolor[i][j] = d;

        }
        fseek(f, pading, SEEK_CUR);

    }

    int count = 0;
    for (int i = 0; i < dib->width; i++) {
        for (int j = 0; j < (int) ceil(dib->height / 8.0); j++) {
            unsigned char c = pixelArraycolor[i][j];
            for (int k = 7; k >= 0; k--) {
                pixelArraycolor2[count] = (c >> k) & 1;
                count++;
            }
        }
        count -= pading2;

    }
     count = 0;

    for (int i = 0; i < dib->width; i++) {
        for (int j = 0; j < (int) ceil(dib->height / 8.0); j++) {
            unsigned char c = 0;
            for (int k = 0; k < 8; k++) {
                c = c + pixelArraycolor2[count];
                c = c << 1;
                count++;
            }
            pixelArraycolor[i][j] = c;
        }
        count -= pading2;

    }
    for (int i = 0; i < dib->width; i++) {
        count = dib->height - 1;
        for (int j = 0; j < dib->height; j++) {
            pixelArraycolor3[i * dib->width + j] = pixelArraycolor2[i * dib->width + count];
            count--;
        }

    }
    count = 0;
    for (int i = 0; i < dib->width; i++) {
        for (int j = 0; j < (int) ceil(dib->height / 8.0); j++) {
            unsigned char c = 0;
            for (int k = 0; k < 8; k++) {
                c = c + pixelArraycolor3[count];
                c = c << 1;
                count++;
            }
            pixelArraycolor4[i][j] = c;
        }
        count -= pading2;

    }
    // count = 0;
    fseek(f, (*bmp).dataoffset, SEEK_SET);
    for (int i = 0; i < dib->width; i++) {
        for (int j = 0; j < (int) (ceil(dib->height / 8.0)); j++) {
            fwrite(&pixelArraycolor[i][j], 1, 1, f);
        }
        unsigned char d = 0x00;
        fwrite(&d, 1, pading, f);

    }
}

void rotate_1bits1(struct BMP *bmp, struct DIB *dib, FILE *f) {
    fseek(f, (*bmp).dataoffset, SEEK_SET);

    int pixelSize = (*dib).height * (*dib).width;


    char pixelArraycolor[pixelSize];
    char pixelArraycolor2[pixelSize];

    char pixelArraycolor3[pixelSize];
    //reshenie na rotate;
    int count = 0;
    for (int i = 0; i < pixelSize - 1; i += 7) {
        // color
        fread(&pixelArraycolor[i], 1, 1, f);
        unsigned char c = pixelArraycolor[i];
        unsigned char c1 = c >> 1;
        c = c << 1;
        unsigned char c2 = c >> 1;
        c = c << 1;
        unsigned char c3 = c >> 1;
        c = c << 1;
        unsigned char c4 = c >> 1;
        c = c << 1;
        unsigned char c5 = c >> 1;
        c = c << 1;
        unsigned char c6 = c >> 1;
        c = c << 1;
        unsigned char c7 = c >> 1;
        c = c << 1;
        unsigned char c8 = c >> 1;


        pixelArraycolor2[count] = c1;
        pixelArraycolor2[count + 1] = c2;
        pixelArraycolor2[count + 2] = c3;
        pixelArraycolor2[count + 3] = c4;
        pixelArraycolor2[count + 4] = c5;
        pixelArraycolor2[count + 5] = c6;
        pixelArraycolor2[count + 6] = c7;
        pixelArraycolor2[count + 7] = c8;
        pixelArraycolor3[count] = c1;
        pixelArraycolor3[count + 1] = c2;
        pixelArraycolor3[count + 2] = c3;
        pixelArraycolor3[count + 3] = c4;
        pixelArraycolor3[count + 4] = c5;
        pixelArraycolor3[count + 5] = c6;
        pixelArraycolor3[count + 6] = c7;
        pixelArraycolor3[count + 7] = c8;
        count += 8;


    }
    int x1 = (*dib).width - 1;
    for (int i = 0; i < (*dib).width; i++) {
        for (int y = 0; y < (*dib).height; y += 1) {
            pixelArraycolor2[y * (*dib).width + x1] = pixelArraycolor3[i * (*dib).width + y];
        }
        x1 -= 1;
    }
    fseek(f, (*bmp).dataoffset, SEEK_SET);
    count = 0;
    for (int i = 0; i < pixelSize - 1; i += 7) {
        unsigned char result = 0;
        result += pixelArraycolor2[count];
        result = result << 1;
        result += pixelArraycolor2[count + 1];
        result = result << 1;
        result += pixelArraycolor2[count + 2];
        result = result << 1;
        result += pixelArraycolor2[count + 3];
        result = result << 1;
        result += pixelArraycolor2[count + 4];
        result = result << 1;
        result += pixelArraycolor2[count + 5];
        result = result << 1;
        result += pixelArraycolor2[count + 6];
        result = result << 1;
        result += pixelArraycolor2[count + 7];
        fwrite(&result, 1, 1, f);
        fseek(f, 0, SEEK_CUR);

        count += 8;
    }
//        int x = 0;
//    while (x < (*dib).width) {
//        int y = 0;
//        while (y < (*dib).height) {
//            unsigned char result = 0;
//            result += pixelArraycolor2[x * (*dib).width + y];
//            result = result << 4;
//            result += pixelArraycolor2[x * (*dib).width + y + 1];
//            fwrite(&result, 1, 1, f);
//            y += 2;
//            fseek(f, 0, SEEK_CUR);
//
//        }
//
//        fseek(f, 0, SEEK_CUR);
//        x++;
//    }

}