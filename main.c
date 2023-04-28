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
int main() {
    struct BMP bmp;
    struct DIB dib;
    struct PIXEL pixel;
    struct PIXEL pixel2;

    FILE *f;
    FILE *f1;

    f = fopen("bmp_24.bmp", "rb+");
    f1 = fopen("bmp_24_1.bmp", "wb+");

    if (f == NULL) {
        perror("Greshka s faila");
        exit(1);
    }
    fread(&bmp.filetype,1 ,2,f);


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

    if (dib.fileheader != 40) {
        printf("Greshen format");
        exit(-1);
    }

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
    switch(dib.bitsperpixel) {
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
            return  1;
    }
//reshenie na invert
/*
    int x = 0;
    while (x < dib.width) {
        int y = 0;
        while (y < dib.height) {

            fread(&pixel.b, 1, 1, f);
            unsigned int blue = pixel.b;
            blue = ~blue;
            pixel.b = (char) blue;
          //  printf("Pixel 1 is %d\n", pixel.b);

            fread(&pixel.g, 1, 1, f);
            unsigned int green = pixel.g;
            green = ~green;
            pixel.g = (char) green;
           // printf("Pixel 2 is %d\n", pixel.g);

            fread(&pixel.r, 1, 1, f);
            unsigned int red = pixel.r;
            red = ~red;
            pixel.r = (char) red;
         //   printf("Pixel 3 is %d\n", pixel.r);

            fseek(f, -3, SEEK_CUR);
            fwrite(&pixel.b, 1, 1, f);
            fwrite(&pixel.g, 1, 1, f);
            fwrite(&pixel.r, 1, 1, f);
            fseek(f, 0, SEEK_CUR);

            y++;
        }
          fseek(f,0,SEEK_CUR);

        x++;
    }*/
    int pixelSize = dib.height * dib.width ;



    char pixelArrayb[pixelSize];
    char pixelArrayg[pixelSize];
    char pixelArrayr[pixelSize];
    char pixelArrayb2[pixelSize];
    char pixelArrayg2[pixelSize];
    char pixelArrayr2[pixelSize];
    int lastIndex = pixelSize-1;
    //reshenie na rotate;
    for(int i = 0; i < pixelSize; i+=1)
    {
        // Blue
        fread(&pixelArrayb[i], 1, 1, f);
        // Green
        fread(&pixelArrayg[(i)], 1, 1, f);
        // Red
        fread(&pixelArrayr[(i)], 1, 1, f);

    }int x1=dib.width-1;
    for (int i = 0; i < dib.width;i++) {
        for (int y = 0; y < dib.height; y++) {
            pixelArrayb2[y*dib.width+x1]=pixelArrayb[i*dib.width+y];
            pixelArrayg2[y*dib.width+x1]=pixelArrayg[i*dib.width+y];
            pixelArrayr2[y*dib.width+x1]=pixelArrayr[i*dib.width+y];
        }x1--;
    }
    fseek(f, bmp.dataoffset, SEEK_SET);

    int x = 0;
    while (x < dib.width) {
        int y = 0;
        while (y < dib.height) {
            fwrite(&pixelArrayb2[x * dib.width + y], 1, 1, f);
            fwrite(&pixelArrayg2[x * dib.width + y], 1, 1, f);
            fwrite(&pixelArrayr2[x * dib.width + y], 1, 1, f);
            y++;
            fseek(f, 0, SEEK_CUR);

        }

        fseek(f, 0, SEEK_CUR);
        x++;
    }
//revenie na flip;

/*
    for(int i = 0; i < pixelSize; i+=1)
    {
        // Blue
        fread(&pixelArrayb[i], 1, 1, f);
        // Green
        fread(&pixelArrayg[(i)], 1, 1, f);
        // Red
        fread(&pixelArrayr[(i)], 1, 1, f);

    }for ( int x = 0; x < dib.width; x++) {
        for (int y = 0; y < dib.height/2; y++) {
            unsigned char b=pixelArrayb[x*dib.width+y];
            unsigned char g=pixelArrayg[x*dib.width+y];
            unsigned char r=pixelArrayr[x*dib.width+y];
            pixelArrayb[x*dib.width+y]=pixelArrayb[x*dib.width+dib.height-y];
            pixelArrayg[x*dib.width+y]=pixelArrayg[x*dib.width+dib.height-y];
            pixelArrayr[x*dib.width+y]=pixelArrayr[x*dib.width+dib.height-y];
            pixelArrayb[x*dib.width+dib.height-y]=b;
            pixelArrayg[x*dib.width+dib.height-y]=g;
            pixelArrayr[x*dib.width+dib.height-y]=r;
        }
    }

    fseek(f, bmp.dataoffset-3, SEEK_SET);

    int x = 0;
    while (x < dib.width) {
        int y = 0;
        while (y < dib.height) {
            fwrite(&pixelArrayb[x * dib.width + y], 1, 1, f);
            fwrite(&pixelArrayg[x * dib.width + y], 1, 1, f);
            fwrite(&pixelArrayr[x * dib.width + y], 1, 1, f);
            y++;
            fseek(f, 0, SEEK_CUR);

        }

        fseek(f, 0, SEEK_CUR);
        x++;
    }
    */
    /*struct PIXEL pixel3[dib.width][dib.height];
    int x = 0;
    while (x < dib.width) {
        int y = 0;
        while (y < dib.height) {
            fread(&pixel3[x][y].b, 1, 1, f);
            fread(&pixel3[x][y].g, 1, 1, f);
            fread(&pixel3[x][y].r, 1, 1, f);
            y++;
        }
        x++;
    }
    for ( x = 0; x < dib.width; x++) {
        for (int y = 0; y < dib.height/2; y++) {
            unsigned char b=pixel3[x][y].b;
            unsigned char g=pixel3[x][y].g;
            unsigned char r=pixel3[x][y].r;
            pixel3[x][y].b=pixel3[x][dib.height-y].b;
            pixel3[x][y].g=pixel3[x][dib.height-y].g;
            pixel3[x][y].r=pixel3[x][dib.height-y].r;
            pixel3[x][dib.height-y].b=b;
            pixel3[x][dib.height-y].g=g;
            pixel3[x][dib.height-y].r=r;
        }
    }


    fseek(f,-dib.width*dib.height*3-3,SEEK_CUR);

    x = 0;
    while (x < dib.width) {
        int y = 0;
        while (y < dib.height) {
            fwrite(&pixel3[x][y].b, 1, 1, f);
            fwrite(&pixel3[x][y].g, 1, 1, f);
            fwrite(&pixel3[x][y].r, 1, 1, f);
            y++;
        }
        x++;
    }
     */
    /*
    int x = 0;
    while (x < dib.width) {
        int y = 0;
        while (y < (int)dib.height/2) {
            if(y==(int)dib.height/2 &&x==dib.width){
                break;
            }

            fread(&pixel.b, 1, 1, f);
            fread(&pixel.g, 1, 1, f);
            fread(&pixel.r, 1, 1, f);

            fseek(f, dib.height*3-((y+1)*3)-2-y*3, SEEK_CUR);

            fread(&pixel2.b, 1, 1, f);
            fread(&pixel2.g, 1, 1, f);
            fread(&pixel2.r, 1, 1, f);

            fseek(f, -(dib.height*3-((y+1)*3)), SEEK_CUR);

            unsigned int b=pixel.b,g=pixel.g,r=pixel.r;

            pixel.b=pixel2.b;
            pixel.g=pixel2.g;
            pixel.r=pixel2.r;
            pixel2.b=(char)b;
            pixel2.g=(char)g;
            pixel2.r=(char)r;

            fwrite(&pixel.b, 1, 1, f);
            fwrite(&pixel.g, 1, 1, f);
            fwrite(&pixel.r, 1, 1, f);
            fseek(f, dib.height*3-((y+1)*3)-2-y*3, SEEK_CUR);
            fwrite(&pixel2.b, 1, 1, f);
            fwrite(&pixel2.g, 1, 1, f);
            fwrite(&pixel2.r, 1, 1, f);
            fseek(f, -(dib.height*3-((y+1)*3)), SEEK_CUR);

            //fseek(f, 0, SEEK_CUR);

            y++;
        }
       // fseek(f,0,SEEK_CUR);

        x++;
    }
*/

    printf("reddy");
    fclose(f);
    fclose(f1);

    return 0;
}
