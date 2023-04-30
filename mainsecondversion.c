//
// Created by Kiril Valkov on 26.04.23.
//
#include <stdio.h>
#include <stdlib.h>

struct BMP {
    char filetype[2]; // must be BM, must check if BM
    unsigned int filesize;
    short reserved1;
    short reserved2;
    unsigned int dataoffset;

};
struct DIB {
    unsigned int fileheader;
    unsigned int headersize;
    int width;
    int height;
    short planes;
    short bitsperpixel; /* we only support the value 24 here */
    unsigned int compression; /* we do not support compression */
    unsigned int bitmapsize;
    int horizontalres;
    int verticalres;
    unsigned int numcolors;
    unsigned int importantcolors;
};

struct PIXEL {
    unsigned char b;
    unsigned char g;
    unsigned char r;

};
struct PIXEL_8 {
    unsigned char color;

};
struct PIXEL_16 {
    unsigned char a_r;
    unsigned char b_g;

};

void fllip_24bits(struct BMP *bmp, struct DIB *dib, FILE *f);

void rotate_24bits(struct BMP *bmp, struct DIB *dib, FILE *f);

void invert_24bits(struct DIB *dib, struct PIXEL *pixel, FILE *f);

void invert_16bits(struct BMP *bmp, struct DIB *dib, struct PIXEL_16 *pixel, FILE *f);

void flip_8bits(struct BMP *bmp, struct DIB *dib, FILE *f);

void rotate_8bits(struct BMP *bmp, struct DIB *dib, FILE *f);

void invert_8bits(struct BMP *bmp, struct DIB *dib, struct PIXEL_8 *pixel_8, FILE *f);

void rotate_16bits(struct BMP *bmp, struct DIB *dib, FILE *f);

void fllip_16bits(struct BMP *bmp, struct DIB *dib, FILE *f);

void invert_4bits(struct BMP *bmp, struct DIB *dib, struct PIXEL_8 *pixel_8, FILE *f);

void flip_4bits(struct BMP *bmp, struct DIB *dib, FILE *f);

void invert_2bits(struct BMP *bmp, struct DIB *dib, struct PIXEL_8 *pixel_8, FILE *f);

void invert_1bits(struct BMP *bmp, struct DIB *dib, struct PIXEL_8 *pixel_8, FILE *f);

void rotate_4bits(struct BMP *bmp, struct DIB *dib, FILE *f);

void flip_1bits(struct BMP *bmp, struct DIB *dib, FILE *f);

int main() {
    struct BMP bmp;
    struct DIB dib;
    struct PIXEL pixel;
    struct PIXEL_8 pixel_8;
    struct PIXEL_16 pixel_16;

    FILE *f;
    FILE *f1;

    f = fopen("bmp_1_indexed.bmp", "rb+");
    f1 = fopen("bmp_24_1.bmp", "wb+");

    if (f == NULL) {
        perror("Greshka s faila");
        exit(1);
    }
    fread(&bmp.filetype, 1, 2, f);


    if (bmp.filetype[0] != 'B' && bmp.filetype[1] != 'M') {
        printf("Greshen format");
        exit(1);
    }


    fread(&bmp.filesize, 4, 1, f);
    printf("Value is %d\n", bmp.filesize);

    fseek(f, 4, SEEK_CUR);

    fread(&bmp.dataoffset, 4, 1, f);
    printf("Offset is %d\n", bmp.dataoffset);


    //   fwrite(&bmp, sizeof(bmp), 1, f1);


    fread(&dib.fileheader, 4, 1, f);
    printf("File header is %d bytes\n", dib.fileheader);

    //if (dib.fileheader != 40) {
    //    printf("Greshen format");
    //   exit(-1);
    //}

    fread(&dib.width, 4, 1, f);
    printf("Width is %d\n", dib.width);

    fread(&dib.height, 4, 1, f);
    printf("Height is %d\n", dib.height);

    fread(&dib.planes, 2, 1, f);
    printf("Color planes is %d\n", dib.planes);


    fread(&dib.bitsperpixel, 2, 1, f);
    printf("Pixels per bit is %d\n", dib.bitsperpixel);

    fread(&dib.compression, 4, 1, f);
    printf("Compression scheme used is %d\n", dib.compression);

    fread(&dib.bitmapsize, 4, 1, f);
    printf("Image size is %d\n", dib.bitmapsize);

    fread(&dib.horizontalres, 4, 1, f);
    printf("Horizontal resolution is %d\n", dib.horizontalres);

    fread(&dib.verticalres, 4, 1, f);
    printf("Vertical resolution is %d\n", dib.verticalres);

    fread(&dib.numcolors, 4, 1, f);
    printf("Number of colors used %d\n", dib.numcolors);

    fread(&dib.importantcolors, 4, 1, f);
    printf("Important colors used %d\n", dib.importantcolors);
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
    ///revenie na flipna 16;

    //fllip_16bits(&bmp, &dib, f);

    ///reshenie na rotate 16 pix

    //rotate_16bits(&bmp, &dib, f);

    ///reshenie na invert 16 pix

    // invert_16bits(&bmp,&dib, &pixel_16, f);

    ///reshenie na invert 8 pix

    //invert_8bits(&bmp,&dib, &pixel_8, f);

    ///reshenie na rotate 8pix

    // rotate_8bits(&bmp, &dib, f);

    ///reshenie na flip 8pix

    // flip_8bits(&bmp, &dib, f);

    ///reshenie na invert na 24 pix

    //  invert_24bits(&dib, &pixel, f);

    ///reshenie na rotate 24pix

    //   rotate_24bits(&bmp, &dib, f);

    ///revenie na flip 24pix;

    //   fllip_24bits(&bmp, &dib, f);

    ///reshenie na invert 4 pix

    // invert_4bits(&bmp,&dib, &pixel_8, f);

    ///reshenie na flip 4pix

    // flip_4bits(&bmp, &dib, f);

    ///reshenie rotate 8pix

    //rotate_4bits(&bmp, &dib, f);

    ///reshenie na invert 2 pix

    // invert_2bits(&bmp,&dib, &pixel_8, f);

    ///reshenie na invert 1 pix

    // invert_1bits(&bmp,&dib, &pixel_8, f);

    ///reshenie na flip 1pix

    flip_1bits(&bmp, &dib, f);

    unsigned char c = 168;
    unsigned char c1 = c >> 4;
    c = c << 4;
    unsigned char c2 = c >> 4;


    printf("%d %d\n", c1, c2);

    unsigned char result = 0;
    result += c2;
    result = result << 4;
    result += c1;
    printf("%d \n", result);

    printf("reddy");
    fclose(f);
    fclose(f1);

    return 0;
}

void flip_1bits(struct BMP *bmp, struct DIB *dib, FILE *f) {
    fseek(f, (*bmp).dataoffset, SEEK_SET);

    int pixelSize = (*dib).height * (*dib).width;


    char pixelArraycolor[pixelSize];
    char pixelArraycolor2[pixelSize];
    char pixelArraycolor3[pixelSize];
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
        pixelArraycolor2[i] = c1;
        pixelArraycolor2[i + 1] = c2;
        pixelArraycolor2[i + 2] = c3;
        pixelArraycolor2[i + 3] = c4;
        pixelArraycolor2[i + 4] = c5;
        pixelArraycolor2[i + 5] = c6;
        pixelArraycolor2[i + 6] = c7;
        pixelArraycolor2[i + 7] = c8;

    }
    for (int x = 0; x < (*dib).width; x++) {
        int x1 = (*dib).height - 1;

        for (int y = 0; y < (*dib).height; y += 1) {

            pixelArraycolor3[x * (*dib).width + y] = pixelArraycolor2[x * (*dib).width + x1];
            x1 -= 1;
        }

    }


    fseek(f, (*bmp).dataoffset, SEEK_SET);
    int x = 0;
    while (x < (*dib).width) {
        int y = 0;
        while (y < (*dib).height) {
            unsigned char result = 0;
            result += pixelArraycolor3[x * (*dib).width + y];
            result = result << 1;
            result += pixelArraycolor3[x * (*dib).width + y + 1];
            result = result << 1;
            result += pixelArraycolor3[x * (*dib).width + y + 2];
            result = result << 1;
            result += pixelArraycolor3[x * (*dib).width + y + 3];
            result = result << 1;
            result += pixelArraycolor3[x * (*dib).width + y + 4];
            result = result << 1;
            result += pixelArraycolor3[x * (*dib).width + y + 5];
            result = result << 1;
            result += pixelArraycolor3[x * (*dib).width + y + 6];
            result = result << 1;
            result += pixelArraycolor3[x * (*dib).width + y + 7];
            fwrite(&result, 1, 1, f);
            y += 7;
            fseek(f, 0, SEEK_CUR);

        }

        fseek(f, 0, SEEK_CUR);
        x++;
    }
}


void invert_1bits(struct BMP *bmp, struct DIB *dib, struct PIXEL_8 *pixel_8, FILE *f) {
    fseek(f, (*bmp).dataoffset, SEEK_SET);
    int x = 0;
    while (x < (*dib).width) {
        int y = 0;
        while (y < (*dib).height) {

            fread(&(*pixel_8).color, 1, 1, f);
            unsigned int color = (*pixel_8).color;
            color = ~color;
            (*pixel_8).color = (char) color;
            //  printf("Pixel 1 is %d\n", pixel.b);



            fseek(f, -1, SEEK_CUR);
            fwrite(&(*pixel_8).color, 1, 1, f);
            y += 7;
            fseek(f, 0, SEEK_CUR);


        }
        fseek(f, 0, SEEK_CUR);

        x += 1;
    }


}

void invert_2bits(struct BMP *bmp, struct DIB *dib, struct PIXEL_8 *pixel_8, FILE *f) {
    fseek(f, (*bmp).dataoffset, SEEK_SET);

    int x = 0;
    while (x < (*dib).width) {
        int y = 0;
        while (y < (*dib).height) {

            fread(&(*pixel_8).color, 1, 1, f);
            unsigned int color = (*pixel_8).color;
            color = ~color;
            (*pixel_8).color = (char) color;
            //  printf("Pixel 1 is %d\n", pixel.b);



            fseek(f, -1, SEEK_CUR);
            fwrite(&(*pixel_8).color, 1, 1, f);
            fseek(f, 0, SEEK_CUR);

            y += 4;
        }
        fseek(f, 0, SEEK_CUR);

        x += 1;
    }
}

void flip_4bits(struct BMP *bmp, struct DIB *dib, FILE *f) {
    fseek(f, (*bmp).dataoffset, SEEK_SET);

    int pixelSize = (*dib).height * (*dib).width;


    char pixelArraycolor[pixelSize];
    char pixelArraycolor2[pixelSize];
    char pixelArraycolor3[pixelSize];
    for (int i = 0; i < pixelSize - 1; i += 2) {
        // color
        fread(&pixelArraycolor[i], 1, 1, f);
        unsigned char c = pixelArraycolor[i];
        unsigned char c1 = c >> 4;
        c = c << 4;
        unsigned char c2 = c >> 4;
        pixelArraycolor2[i] = c1;
        pixelArraycolor2[i + 1] = c2;

    }
    for (int x = 0; x < (*dib).width; x++) {
        int x1 = (*dib).height - 1;

        for (int y = 0; y < (*dib).height; y += 1) {

            pixelArraycolor3[x * (*dib).width + y] = pixelArraycolor2[x * (*dib).width + x1];
            x1 -= 1;
        }

    }


    fseek(f, (*bmp).dataoffset, SEEK_SET);
    int x = 0;
    while (x < (*dib).width) {
        int y = 0;
        while (y < (*dib).height) {
            unsigned char result = 0;
            result += pixelArraycolor3[x * (*dib).width + y];
            result = result << 4;
            result += pixelArraycolor3[x * (*dib).width + y + 1];
            fwrite(&result, 1, 1, f);
            y += 2;
            fseek(f, 0, SEEK_CUR);

        }

        fseek(f, 0, SEEK_CUR);
        x++;
    }
}

void rotate_4bits(struct BMP *bmp, struct DIB *dib, FILE *f) {
    fseek(f, (*bmp).dataoffset, SEEK_SET);

    int pixelSize = (*dib).height * (*dib).width;


    char pixelArraycolor[pixelSize];
    char pixelArraycolor2[pixelSize];

    char pixelArraycolor3[pixelSize];
    //reshenie na rotate;
    for (int i = 0; i < pixelSize - 1; i += 2) {
        // color
        fread(&pixelArraycolor[i], 1, 1, f);
        unsigned char c = pixelArraycolor[i];
        unsigned char c1 = c >> 4;
        c = c << 4;
        unsigned char c2 = c >> 4;
        pixelArraycolor2[i] = c1;
        pixelArraycolor2[i + 1] = c2;
        pixelArraycolor3[i] = c1;
        pixelArraycolor3[i + 1] = c2;


    }
    int x1 = (*dib).width - 1;
    for (int i = 0; i < (*dib).width; i++) {
        for (int y = 0; y < (*dib).height; y += 1) {
            pixelArraycolor2[y * (*dib).width + x1] = pixelArraycolor3[i * (*dib).width + y];
        }
        x1 -= 1;
    }
    fseek(f, (*bmp).dataoffset, SEEK_SET);

    int x = 0;
    while (x < (*dib).width) {
        int y = 0;
        while (y < (*dib).height) {
            unsigned char result = 0;
            result += pixelArraycolor2[x * (*dib).width + y];
            result = result << 4;
            result += pixelArraycolor2[x * (*dib).width + y + 1];
            fwrite(&result, 1, 1, f);
            y += 2;
            fseek(f, 0, SEEK_CUR);

        }

        fseek(f, 0, SEEK_CUR);
        x++;
    }
}

void invert_4bits(struct BMP *bmp, struct DIB *dib, struct PIXEL_8 *pixel_8, FILE *f) {
    fseek(f, (*bmp).dataoffset, SEEK_SET);

    int x = 0;
    while (x < (*dib).width) {
        int y = 0;
        while (y < (*dib).height) {

            fread(&(*pixel_8).color, 1, 1, f);
            unsigned int color = (*pixel_8).color;
            color = ~color;
            (*pixel_8).color = (char) color;
            //  printf("Pixel 1 is %d\n", pixel.b);



            fseek(f, -1, SEEK_CUR);
            fwrite(&(*pixel_8).color, 1, 1, f);
            fseek(f, 0, SEEK_CUR);

            y += 2;
        }
        fseek(f, 0, SEEK_CUR);

        x += 1;
    }
}

void fllip_16bits(struct BMP *bmp, struct DIB *dib, FILE *f) {
    int pixelSize = (*dib).height * (*dib).width;
    fseek(f, (*bmp).dataoffset, SEEK_SET);


    char pixelArrayb[pixelSize];
    char pixelArrayg[pixelSize];
    char pixelArrayb2[pixelSize];
    char pixelArrayg2[pixelSize];
    for (int i = 0; i < pixelSize; i += 1) {
        // Blue
        fread(&pixelArrayb[i], 1, 1, f);
        // Green
        fread(&pixelArrayg[(i)], 1, 1, f);
        // Red

    }
    for (int x = 0; x < (*dib).width; x++) {
        int x1 = (*dib).height - 1;

        for (int y = 0; y < (*dib).height; y++) {

            pixelArrayb2[x * (*dib).width + y] = pixelArrayb[x * (*dib).width + x1];
            pixelArrayg2[x * (*dib).width + y] = pixelArrayg[x * (*dib).width + x1];
            x1--;
        }

    }

    fseek(f, (*bmp).dataoffset, SEEK_SET);

    int x = 0;
    while (x < (*dib).width) {
        int y = 0;
        while (y < (*dib).height) {
            fwrite(&pixelArrayb2[x * (*dib).width + y], 1, 1, f);
            fwrite(&pixelArrayg2[x * (*dib).width + y], 1, 1, f);
            y++;
            fseek(f, 0, SEEK_CUR);

        }

        fseek(f, 0, SEEK_CUR);
        x++;
    }
}

void rotate_16bits(struct BMP *bmp, struct DIB *dib, FILE *f) {
    int pixelSize = (*dib).height * (*dib).width;

    fseek(f, (*bmp).dataoffset, SEEK_SET);

    char pixelArrayb[pixelSize];
    char pixelArrayg[pixelSize];
    char pixelArrayb2[pixelSize];
    char pixelArrayg2[pixelSize];

    for (int i = 0; i < pixelSize; i += 1) {
        // Blue
        fread(&pixelArrayb[i], 1, 1, f);
        // Green
        fread(&pixelArrayg[(i)], 1, 1, f);

    }
    int x1 = (*dib).width - 1;
    for (int i = 0; i < (*dib).width; i++) {
        for (int y = 0; y < (*dib).height; y++) {
            pixelArrayb2[y * (*dib).width + x1] = pixelArrayb[i * (*dib).width + y];
            pixelArrayg2[y * (*dib).width + x1] = pixelArrayg[i * (*dib).width + y];
        }
        x1--;
    }
    fseek(f, (*bmp).dataoffset, SEEK_SET);

    int x = 0;
    while (x < (*dib).width) {
        int y = 0;
        while (y < (*dib).height) {
            fwrite(&pixelArrayb2[x * (*dib).width + y], 1, 1, f);
            fwrite(&pixelArrayg2[x * (*dib).width + y], 1, 1, f);
            y++;
            fseek(f, 0, SEEK_CUR);

        }

        fseek(f, 0, SEEK_CUR);
        x++;
    }
}

void invert_16bits(struct BMP *bmp, struct DIB *dib, struct PIXEL_16 *pixel, FILE *f) {
    fseek(f, (*bmp).dataoffset, SEEK_SET);

    int x = 0;
    while (x < (*dib).width) {
        int y = 0;
        while (y < (*dib).height) {


            fread(&(*pixel).b_g, 1, 1, f);
            unsigned int blue = (*pixel).b_g;
            blue = ~blue;
            (*pixel).b_g = (char) blue;
            //  printf("Pixel 1 is %d\n", pixel.b);

            fread(&(*pixel).a_r, 1, 1, f);
            unsigned int green = (*pixel).a_r;
            green = ~green;
            (*pixel).a_r = (char) green;
            // printf("Pixel 2 is %d\n", pixel.g);


            fseek(f, -2, SEEK_CUR);
            fwrite(&(*pixel).b_g, 1, 1, f);
            fwrite(&(*pixel).a_r, 1, 1, f);
            fseek(f, 0, SEEK_CUR);

            y++;
        }
        fseek(f, 0, SEEK_CUR);

        x++;
    }
}

void invert_8bits(struct BMP *bmp, struct DIB *dib, struct PIXEL_8 *pixel_8, FILE *f) {
    fseek(f, (*bmp).dataoffset, SEEK_SET);

    int x = 0;
    while (x < (*dib).width) {
        int y = 0;
        while (y < (*dib).height) {

            fread(&(*pixel_8).color, 1, 1, f);
            unsigned int color = (*pixel_8).color;
            color = ~color;
            (*pixel_8).color = (char) color;
            //  printf("Pixel 1 is %d\n", pixel.b);



            fseek(f, -1, SEEK_CUR);
            fwrite(&(*pixel_8).color, 1, 1, f);
            fseek(f, 0, SEEK_CUR);

            y++;
        }
        fseek(f, 0, SEEK_CUR);

        x++;
    }
}

void rotate_8bits(struct BMP *bmp, struct DIB *dib, FILE *f) {
    fseek(f, (*bmp).dataoffset, SEEK_SET);

    int pixelSize = (*dib).height * (*dib).width;


    char pixelArraycolor[pixelSize];
    char pixelArraycolor2[pixelSize];
    //reshenie na rotate;
    for (int i = 0; i < pixelSize; i += 1) {
        // color
        fread(&pixelArraycolor[i], 1, 1, f);

    }
    int x1 = (*dib).width - 1;
    for (int i = 0; i < (*dib).width; i++) {
        for (int y = 0; y < (*dib).height; y++) {
            pixelArraycolor2[y * (*dib).width + x1] = pixelArraycolor[i * (*dib).width + y];
        }
        x1--;
    }
    fseek(f, (*bmp).dataoffset, SEEK_SET);

    int x = 0;
    while (x < (*dib).width) {
        int y = 0;
        while (y < (*dib).height) {
            fwrite(&pixelArraycolor2[x * (*dib).width + y], 1, 1, f);
            y++;
            fseek(f, 0, SEEK_CUR);

        }

        fseek(f, 0, SEEK_CUR);
        x++;
    }
}

void flip_8bits(struct BMP *bmp, struct DIB *dib, FILE *f) {
    fseek(f, (*bmp).dataoffset, SEEK_SET);

    int pixelSize = (*dib).height * (*dib).width;


    char pixelArraycolor[pixelSize];
    char pixelArraycolor2[pixelSize];

    for (int i = 0; i < pixelSize; i += 1) {
        // color
        fread(&pixelArraycolor[i], 1, 1, f);
    }
    for (int x = 0; x < (*dib).width; x++) {
        int x1 = (*dib).height - 1;

        for (int y = 0; y < (*dib).height; y++) {

            pixelArraycolor2[x * (*dib).width + y] = pixelArraycolor[x * (*dib).width + x1];
            x1--;
        }

    }

    fseek(f, (*bmp).dataoffset, SEEK_SET);

    int x = 0;
    while (x < (*dib).width) {
        int y = 0;
        while (y < (*dib).height) {
            fwrite(&pixelArraycolor2[x * (*dib).width + y], 1, 1, f);
            y++;
            fseek(f, 0, SEEK_CUR);

        }

        fseek(f, 0, SEEK_CUR);
        x++;
    }
}

void invert_24bits(struct DIB *dib, struct PIXEL *pixel, FILE *f) {
    int x = 0;
    while (x < (*dib).width) {
        int y = 0;
        while (y < (*dib).height) {

            fread(&(*pixel).b, 1, 1, f);
            unsigned int blue = (*pixel).b;
            blue = ~blue;
            (*pixel).b = (char) blue;
            //  printf("Pixel 1 is %d\n", pixel.b);

            fread(&(*pixel).g, 1, 1, f);
            unsigned int green = (*pixel).g;
            green = ~green;
            (*pixel).g = (char) green;
            // printf("Pixel 2 is %d\n", pixel.g);

            fread(&(*pixel).r, 1, 1, f);
            unsigned int red = (*pixel).r;
            red = ~red;
            (*pixel).r = (char) red;
            //   printf("Pixel 3 is %d\n", pixel.r);

            fseek(f, -3, SEEK_CUR);
            fwrite(&(*pixel).b, 1, 1, f);
            fwrite(&(*pixel).g, 1, 1, f);
            fwrite(&(*pixel).r, 1, 1, f);
            fseek(f, 0, SEEK_CUR);

            y++;
        }
        fseek(f, 0, SEEK_CUR);

        x++;
    }
}

void rotate_24bits(struct BMP *bmp, struct DIB *dib, FILE *f) {
    int pixelSize = (*dib).height * (*dib).width;


    char pixelArrayb[pixelSize];
    char pixelArrayg[pixelSize];
    char pixelArrayr[pixelSize];
    char pixelArrayb2[pixelSize];
    char pixelArrayg2[pixelSize];
    char pixelArrayr2[pixelSize];
    int lastIndex = pixelSize - 1;
    ///reshenie na rotate;

    for (int i = 0; i < pixelSize; i += 1) {
        // Blue
        fread(&pixelArrayb[i], 1, 1, f);
        // Green
        fread(&pixelArrayg[(i)], 1, 1, f);
        // Red
        fread(&pixelArrayr[(i)], 1, 1, f);

    }
    int x1 = (*dib).width - 1;
    for (int i = 0; i < (*dib).width; i++) {
        for (int y = 0; y < (*dib).height; y++) {
            pixelArrayb2[y * (*dib).width + x1] = pixelArrayb[i * (*dib).width + y];
            pixelArrayg2[y * (*dib).width + x1] = pixelArrayg[i * (*dib).width + y];
            pixelArrayr2[y * (*dib).width + x1] = pixelArrayr[i * (*dib).width + y];
        }
        x1--;
    }
    fseek(f, (*bmp).dataoffset, SEEK_SET);

    int x = 0;
    while (x < (*dib).width) {
        int y = 0;
        while (y < (*dib).height) {
            fwrite(&pixelArrayb2[x * (*dib).width + y], 1, 1, f);
            fwrite(&pixelArrayg2[x * (*dib).width + y], 1, 1, f);
            fwrite(&pixelArrayr2[x * (*dib).width + y], 1, 1, f);
            y++;
            fseek(f, 0, SEEK_CUR);

        }

        fseek(f, 0, SEEK_CUR);
        x++;
    }
}

void fllip_24bits(struct BMP *bmp, struct DIB *dib, FILE *f) {
    int pixelSize = (*dib).height * (*dib).width;


    char pixelArrayb[pixelSize];
    char pixelArrayg[pixelSize];
    char pixelArrayr[pixelSize];
    char pixelArrayb2[pixelSize];
    char pixelArrayg2[pixelSize];
    char pixelArrayr2[pixelSize];
    for (int i = 0; i < pixelSize; i += 1) {
        // Blue
        fread(&pixelArrayb[i], 1, 1, f);
        // Green
        fread(&pixelArrayg[(i)], 1, 1, f);
        // Red
        fread(&pixelArrayr[(i)], 1, 1, f);

    }
    for (int x = 0; x < (*dib).width; x++) {
        int x1 = (*dib).height - 1;

        for (int y = 0; y < (*dib).height; y++) {

            pixelArrayb2[x * (*dib).width + y] = pixelArrayb[x * (*dib).width + x1];
            pixelArrayg2[x * (*dib).width + y] = pixelArrayg[x * (*dib).width + x1];
            pixelArrayr2[x * (*dib).width + y] = pixelArrayr[x * (*dib).width + x1];
            x1--;
        }

    }

    fseek(f, (*bmp).dataoffset, SEEK_SET);

    int x = 0;
    while (x < (*dib).width) {
        int y = 0;
        while (y < (*dib).height) {
            fwrite(&pixelArrayb2[x * (*dib).width + y], 1, 1, f);
            fwrite(&pixelArrayg2[x * (*dib).width + y], 1, 1, f);
            fwrite(&pixelArrayr2[x * (*dib).width + y], 1, 1, f);
            y++;
            fseek(f, 0, SEEK_CUR);

        }

        fseek(f, 0, SEEK_CUR);
        x++;
    }
}
