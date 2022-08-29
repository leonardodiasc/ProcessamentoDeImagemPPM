#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int r;
    int g;
    int b;
} Pixel;


int saturacao(int v);

Pixel** rotateImgLeft(Pixel** filtered,int height, int width);

Pixel** rotateImgRight(Pixel** filtered,int height, int width);

Pixel** rotateImgUpsideDown(Pixel** filtered, int height, int width);

Pixel** applyFilterTresholding(Pixel** filtered, Pixel** newImg,int height, int width);

Pixel** applyFilterSharpen(Pixel** filtered, Pixel** newImg,int height, int width);

Pixel** applyFilterBlur(Pixel** filtered, Pixel** newImg,int height, int width);

Pixel** applyFilterGauss(Pixel** filtered, Pixel** newImg,int height, int width);

void save_image(char* name, Pixel** img, int width, int height);

Pixel** get_image(FILE* img, Pixel ** newImg,int* height, int* width);

Pixel** amplifyImage (Pixel** Img, int height, int width, int *pHeight, int *pWidth);

Pixel** reduceImage (Pixel** Img, int height, int width, int *pHeight, int *pWidth);

Pixel** edgeDetection(Pixel** filtered, Pixel** newImg,int height, int width);
