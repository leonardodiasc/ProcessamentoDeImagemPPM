#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "filters.h"
/* Funcao que faz a saturacao de pixels
    Entrada: v: o pixel a receber a saturacao
    Saida: caso v tenha valor maior que 255 ela retorna 255, caso v tenha valor menor que 0 ela retorna 0, caso v esteja entre 0 e 255 o proprio valor de v eh retornado */
int saturacao(int v) {
    if (v > 255) return 255;
    if (v < 0) return 0;
    return v;
}

/* Funcao que amplifica a imagem recebida em 2x
    Entradas: Img: a imagem original(matrix de pixels)
              height: a altura da imagem original
              width: a largura da imagem original
              pHeight: um ponteiro para atualizar o valor de height na main
              pWidth: um ponteiro para atualizar o valor de width na main
    Saida: Uma nova matriz de pixels duas vezes aumentada,
            usando interpolacao para calcular os novos espacos*/
Pixel** amplifyImage (Pixel** Img, int height, int width, int *pHeight, int *pWidth){
    int count, scount,i,j;
    int newHeight, newWidth;
    Pixel **amp, d, e; 

    newHeight = height * 2;
    newWidth = width * 2;
    *pWidth = newWidth;
    *pHeight = newHeight;

    amp = (Pixel**) malloc(sizeof(Pixel*) * newWidth);

    for (count = 0; count < newWidth; ++count)
    {
        amp[count] = (Pixel*) malloc(sizeof(Pixel) * newHeight);
    }

    for (count = 0; count < height ; ++count)
    {

        for ( scount = 0; scount + 1 < width ; ++scount)
        {

            amp[scount * 2][count * 2].r = Img[scount][count].r;
            amp[scount * 2][count * 2].g = Img[scount][count].g;
            amp[scount * 2][count * 2].b = Img[scount][count].b;

            amp[scount * 2 + 1][count * 2].r = (Img[scount + 1][count].r +Img[scount][count].r)/2;
            amp[scount * 2 + 1][count * 2].g = (Img[scount + 1][count].g + Img[scount][count].g)/2;
            amp[scount * 2 + 1][count * 2].b = (Img[scount + 1][count].b + Img[scount][count].b)/2;

            amp[scount * 2][count * 2 + 1].r = (Img[scount][count].r + Img[scount][count + 1].r)/2;
            amp[scount * 2][count * 2 + 1].g = (Img[scount][count].g + Img[scount][count + 1].g)/2;
            amp[scount * 2][count * 2 + 1].b = (Img[scount][count].b + Img[scount][count + 1].b)/2;

            d.r = (Img[scount + 1][count].r + Img[scount + 1][count + 1].r)/2;
            d.g = (Img[scount + 1][count].g + Img[scount + 1][count + 1].g)/2;
            d.b = (Img[scount + 1][count].b + Img[scount + 1][count + 1].b)/2;
            e.r = (Img[scount][count + 1].r + Img[scount + 1][count + 1].r)/2;
            e.g = (Img[scount][count + 1].g + Img[scount + 1][count + 1].g)/2;
            e.b = (Img[scount][count + 1].b + Img[scount + 1][count + 1].b)/2;

            amp[scount * 2 + 1][count * 2 + 1].r = ((Img[scount][count].r + Img[scount][count + 1].r)/2 + (Img[scount + 1][count].r +Img[scount][count].r)/2 + d.r + e.r)/4;
            amp[scount * 2 + 1][count * 2 + 1].g = ((Img[scount][count].g + Img[scount][count + 1].g)/2 + (Img[scount + 1][count].g +Img[scount][count].g)/2 + d.g + e.g)/4;
            amp[scount * 2 + 1][count * 2 + 1].b = ((Img[scount][count].b + Img[scount][count + 1].b)/2 + (Img[scount + 1][count].b +Img[scount][count].b)/2 + d.b + e.b)/4;
        }
    }

    return amp;
}

/* Funcao que reduz a imagem recebida em 2x
    Entradas: Img: a imagem original(matrix de pixels)
              height: a altura da imagem original
              width: a largura da imagem original
              pHeight: um ponteiro para atualizar o valor de height na main
              pWidth: um ponteiro para atualizar o valor de width na main
    Saida:    Uma nova matrix de pixels com reducao de duas vezes*/
Pixel** reduceImage (Pixel** Img, int height, int width, int *pHeight, int *pWidth){
    int count, scount, i, j, cont;
    int newHeight, newWidth;
    Pixel d, e;
    Pixel **amp; 
    newHeight = height /2;
    newWidth = width /2;
    *pWidth = newWidth;
    *pHeight = newHeight;

    amp = (Pixel**) malloc(sizeof(Pixel*) * newWidth);

    for (count = 0; count < newWidth; ++count)
    {
        amp[count] = (Pixel*) malloc(sizeof(Pixel) * newHeight);
    }

    for (count = 1; count + 1 < height ; ++count)
    {

        for ( scount = 1; scount + 2 < width ; ++scount)
        {
            amp[scount / 2][count / 2].r = Img[scount][count].r;
            amp[scount / 2][count / 2].g = Img[scount][count].g;
            amp[scount / 2][count / 2].b = Img[scount][count].b;
        }
    }

    return amp;
}
/* Funcao que rotaciona a imagem para direita
    Entradas: Img: a imagem original(matrix de pixels)
        height: a altura da imagem original
        width: a largura da imagem original
    Saida:    Uma nova matriz de pixels rotacionada para direita*/
Pixel** rotateImgRight(Pixel** filtered,int height, int width)
{
    Pixel** inverted;
    int i,b,count;
    inverted = (Pixel**) malloc(sizeof(Pixel*) * height);

    for ( count = 0; count < height ; ++count)
    {
        inverted[count] = (Pixel*) malloc(sizeof(Pixel) * (width));
    }
    for (i = 1; i < height ; ++i)
    {
        for ( b = 1; b < width ; ++b)
        {
            inverted[height - b][width - i] = filtered[i][b];
        }
    }

    return inverted;
}

/* Funcao que rotaciona a imagem para esquerda
    Entradas: Img: a imagem original(matrix de pixels)
              height: a altura da imagem original
              width: a largura da imagem original
    Saida:    Uma nova matriz de pixels rotacionada para esquerda*/
Pixel** rotateImgLeft(Pixel** filtered,int height, int width)
{
    Pixel** inverted;
    int i,b,count,mi,mb;
    mb = width/2;
    mi = height/2;
    inverted = (Pixel**) malloc(sizeof(Pixel*) * height);

    for ( count = 0; count < height ; ++count)
    {
        inverted[count] = (Pixel*) malloc(sizeof(Pixel) * (width));
    }

    for (i = 1; i < height ; ++i)
    {
        for ( b = 1; b < width ; ++b)
        {
            inverted[b][i] = filtered[i][b];
        }
    }

    return inverted;
}

/* Funcao que rotaciona a imagem em 180o
    Entradas: Img: a imagem original(matrix de pixels)
              height: a altura da imagem original
              width: a largura da imagem original
    Saida:    Uma nova matriz de pixels rotacionada em 180o*/
Pixel** rotateImgUpsideDown(Pixel** filtered, int height, int width)
{
    Pixel** inverted;
    int i,b,count,mi,mb;
    inverted = (Pixel**) malloc(sizeof(Pixel*) * width);

    for ( count = 0; count < width ; ++count)
    {
        inverted[count] = (Pixel*) malloc(sizeof(Pixel) * (height));
    }
    for (i = 1; i < height ; ++i)
    {
        for ( b = 1; b < width ; ++b)
        {
            inverted[height - i][width - b] = filtered[i][b];
        }
    }

    return inverted;
}

/* Funcao que binariza a imagem
    Entradas: newImg: a imagem original(matrix de pixels)
              filtered: imagem usada para a aplicacao da saturacao.
              height: a altura da imagem original
              width: a largura da imagem original
    Saida:    Uma nova matriz de pixels binarizada*/
Pixel** applyFilterTresholding(Pixel** filtered, Pixel** newImg,int height, int width) {
    int i;
    int b;
    int acc;
    long int tresh = 0, treshr = 0,treshg = 0,treshb = 0;

    for (i = 0; i < height ; ++i)
    {
        for ( b = 0; b < width ; ++b)
        {
            treshr = (newImg[i][b].r/10) + treshr;
            treshg = (newImg[i][b].g/10) + treshg;
            treshb = (newImg[i][b].b/10) + treshb;
        }
    }

    tresh = treshr/(height*width);
    tresh += treshg/(height*width);
    tresh+= treshb/(height*width);
    tresh = (tresh*10)/3;
    tresh = tresh + 10;

    for (i = 0; i < height ; ++i)
    {
        for ( b = 0; b < width; ++b)
        {
            if ((newImg[i][b].r + newImg[i][b].g + newImg[i][b].b)/3 > tresh)
            {
                newImg[i][b].r = 255;
                newImg[i][b].g = 255;
                newImg[i][b].b = 255;
            }
            else{
                newImg[i][b].r = 1;
                newImg[i][b].g = 1;
                newImg[i][b].b = 1;
            }

            filtered[i][b].r = newImg[i][b].r;
            filtered[i][b].g = newImg[i][b].g;
            filtered[i][b].b = newImg[i][b].b;
        }
    }

    printf("Tresholding filter applied.\nImage saved as 'new_img.ppm'\n");

    return filtered;
}

/* Funcao que aplica o filtro sharpen na imagem
    Entradas: newImg: a imagem original(matrix de pixels)
              filtered: imagem usada para a aplicacao da saturacao.
              height: a altura da imagem original
              width: a largura da imagem original
    Saida:    Uma nova imagem mais nitida*/
Pixel** applyFilterSharpen(Pixel** filtered, Pixel** newImg,int height, int width) {
    int i;
    int b;
    int acc;
    for (i = 1; i < height - 1; ++i)
    {
        for ( b = 1; b < width - 1; ++b)
        {
            acc = newImg[i][b].r * 5;
            acc += newImg[i-1][b].r * -1; /* vizinho de cima */
            acc += newImg[i+1][b].r * -1; /* vizinho de baixo */
            acc += newImg[i][b-1].r * -1; /* vizinho da esquerda */
            acc += newImg[i][b+1].r * -1; /* vizinho da direita */
            acc += newImg[i-1][b-1].r * 0; /* vizinho superior esquerdo */
            acc += newImg[i-1][b+1].r * 0; /* vizinho superior direito */
            acc += newImg[i+1][b-1].r * 0; /* vizinho inferior esquerdo */
            acc += newImg[i+1][b+1].r * 0; /* vizinho inferior direito */

            filtered[i][b].r = saturacao(acc);

            acc = newImg[i][b].g * 5;
            acc += newImg[i-1][b].g * -1; /* vizinho de cima */
            acc += newImg[i+1][b].g * -1; /* vizinho de baixo */
            acc += newImg[i][b-1].g * -1; /* vizinho da esquerda */
            acc += newImg[i][b+1].g * -1; /* vizinho da direita */
            acc += newImg[i-1][b-1].g * 0; /* vizinho superior esquerdo */
            acc += newImg[i-1][b+1].g * 0; /* vizinho superior direito */
            acc += newImg[i+1][b-1].g * 0; /* vizinho inferior esquerdo */
            acc += newImg[i+1][b+1].g * 0; /* vizinho inferior direito */

            filtered[i][b].g = saturacao(acc);

            acc = newImg[i][b].b * 5;
            acc += newImg[i-1][b].b * -1; /* vizinho de cima */
            acc += newImg[i+1][b].b * -1; /* vizinho de baixo */
            acc += newImg[i][b-1].b * -1; /* vizinho da esquerda */
            acc += newImg[i][b+1].b * -1; /* vizinho da direita */
            acc += newImg[i-1][b-1].b * 0; /* vizinho superior esquerdo */
            acc += newImg[i-1][b+1].b * 0; /* vizinho superior direito */
            acc += newImg[i+1][b-1].b * 0; /* vizinho inferior esquerdo */
            acc += newImg[i+1][b+1].b * 0; /* vizinho inferior direito */

            filtered[i][b].b = saturacao(acc);

        }
    }

    printf("Sharpen filter applied.\nImage will be saved as 'new_img.ppm'\n");

    return filtered;
}

/* Funcao que aplica o filtro de deteccao de bordas na imagem
    Entradas: newImg: a imagem original(matrix de pixels)
              filtered: imagem usada para a aplicacao da saturacao.
              height: a altura da imagem original
              width: a largura da imagem original
    Saida:    Uma nova imagem com bordas visiveis e fundo preto*/
Pixel** edgeDetection(Pixel** filtered, Pixel** newImg,int height, int width) {
    int i;
    int b;
    int acc;

    for (i = 1; i < height - 1; ++i)
    {
        for ( b = 1; b < width - 1; ++b)
        {
            acc = newImg[i][b].r * 0;
            acc += newImg[i-1][b].r * 0; /* vizinho de cima */
            acc += newImg[i+1][b].r * 0; /* vizinho de baixo */
            acc += newImg[i][b-1].r * 0; /* vizinho da esquerda */
            acc += newImg[i][b+1].r * 0; /* vizinho da direita */
            acc += newImg[i-1][b-1].r * 1; /* vizinho superior esquerdo */
            acc += newImg[i-1][b+1].r * -1; /* vizinho superior direito */
            acc += newImg[i+1][b-1].r * -1; /* vizinho inferior esquerdo */
            acc += newImg[i+1][b+1].r * 1; /* vizinho inferior direito */

            filtered[i][b].r = saturacao(acc);

            acc = newImg[i][b].g * 0;
            acc += newImg[i-1][b].g * 0; /* vizinho de cima */
            acc += newImg[i+1][b].g * 0; /* vizinho de baixo */
            acc += newImg[i][b-1].g * 0; /* vizinho da esquerda */
            acc += newImg[i][b+1].g * 0; /* vizinho da direita */
            acc += newImg[i-1][b-1].g * 1; /* vizinho superior esquerdo */
            acc += newImg[i-1][b+1].g * -1; /* vizinho superior direito */
            acc += newImg[i+1][b-1].g * -1; /* vizinho inferior esquerdo */
            acc += newImg[i+1][b+1].g * 1; /* vizinho inferior direito */

            filtered[i][b].g = saturacao(acc);

            acc = newImg[i][b].b * 0;
            acc += newImg[i-1][b].b * 0; /* vizinho de cima */
            acc += newImg[i+1][b].b * 0; /* vizinho de baixo */
            acc += newImg[i][b-1].b * 0; /* vizinho da esquerda */
            acc += newImg[i][b+1].b * 0; /* vizinho da direita */
            acc += newImg[i-1][b-1].b * 1; /* vizinho superior esquerdo */
            acc += newImg[i-1][b+1].b * -1; /* vizinho superior direito */
            acc += newImg[i+1][b-1].b * -1; /* vizinho inferior esquerdo */
            acc += newImg[i+1][b+1].b * 1; /* vizinho inferior direito */

            filtered[i][b].b = saturacao(acc);

        }
    }

    printf("Sharpen filter applied.\nImage will be saved as 'new_img.ppm'\n");

    return filtered;
}

/* Funcao que aplica o filtro Blur na imagem
    Entradas: newImg: a imagem original(matrix de pixels)
              filtered: imagem usada para a aplicacao da saturacao.
              height: a altura da imagem original
              width: a largura da imagem original
    Saida:    Uma nova imagem suavizada*/
Pixel** applyFilterBlur(Pixel** filtered, Pixel** newImg,int height, int width) {
    int i;
    int b;
    int acc;

    for (i = 1; i < height - 1; ++i)
    {
        for ( b = 1; b < width - 1; ++b)
        {
            acc = newImg[i][b].r * 1/9.0;
            acc += newImg[i-1][b].r * 1/9.0; /* vizinho de cima */
            acc += newImg[i+1][b].r * 1/9.0; /* vizinho de baixo */
            acc += newImg[i][b-1].r * 1/9.0; /* vizinho da esquerda */
            acc += newImg[i][b+1].r * 1/9.0; /* vizinho da direita */
            acc += newImg[i-1][b-1].r * 1/9.0; /* vizinho superior esquerdo */
            acc += newImg[i-1][b+1].r * 1/9.0; /* vizinho superior direito */
            acc += newImg[i+1][b-1].r * 1/9.0; /* vizinho inferior esquerdo */
            acc += newImg[i+1][b+1].r * 1/9.0; /* vizinho inferior direito */

            filtered[i][b].r = saturacao(acc);

            acc = newImg[i][b].g * 1/9.0;
            acc += newImg[i-1][b].g * 1/9.0; /* vizinho de cima */
            acc += newImg[i+1][b].g * 1/9.0; /* vizinho de baixo */
            acc += newImg[i][b-1].g * 1/9.0; /* vizinho da esquerda */
            acc += newImg[i][b+1].g * 1/9.0; /* vizinho da direita */
            acc += newImg[i-1][b-1].g * 1/9.0; /* vizinho superior esquerdo */
            acc += newImg[i-1][b+1].g * 1/9.0; /* vizinho superior direito */
            acc += newImg[i+1][b-1].g * 1/9.0; /* vizinho inferior esquerdo */
            acc += newImg[i+1][b+1].g * 1/9.0; /* vizinho inferior direito */

            filtered[i][b].g = saturacao(acc);

            acc = newImg[i][b].b * 1/9.0;
            acc += newImg[i-1][b].b * 1/9.0; /* vizinho de cima */
            acc += newImg[i+1][b].b * 1/9.0; /* vizinho de baixo */
            acc += newImg[i][b-1].b * 1/9.0; /* vizinho da esquerda */
            acc += newImg[i][b+1].b * 1/9.0; /* vizinho da direita */
            acc += newImg[i-1][b-1].b * 1/9.0; /* vizinho superior esquerdo */
            acc += newImg[i-1][b+1].b * 1/9.0; /* vizinho superior direito */
            acc += newImg[i+1][b-1].b * 1/9.0; /* vizinho inferior esquerdo */
            acc += newImg[i+1][b+1].b * 1/9.0; /* vizinho inferior direito */

            filtered[i][b].b = saturacao(acc);

        }
    }

    printf("Blur filter applied. \nImage will be saved as 'new_img.ppm'\n");

    return filtered;
}

/* Funcao que salva os dados de uma matriz Pixel passada por parametro em um arquivo ppm.
    Entradas:   img: Matriz de Pixel com os dados da imagem.
                name: Nome do arquivo a ser salvo.
                width: Largura da imagem
                height: Altura da imagem.
    Saida: Um arquivo eh salvo com o nome passado por parametro.
*/
void save_image(char* name, Pixel** img, int width, int height) {
    FILE* file;
    int i;
    int j;

    file = fopen(name, "w");

    fprintf(file, "P3\n%i %i\n255\n", width, height);
    for (i = 0; i < width; ++i) 
    {
        for (j = 0; j < height; ++j) 
        {
            fprintf(file, "%i %i %i\n", img[i][j].r, img[i][j].g, img[i][j].b);
        }
    }

    fclose(file);
}

/* 
Funcao que realiza leitura de um arquivo PPM e aloca uma matriz de acordo com o tamanho descrito.
   Entradas: img: Arquivo PPM
             newImg: Matriz de Pixel representando a imagem
             height: Altura da imagem (linhas)
             width: Largura da imagem (colunas)
    Saida: Uma matriz de Pixels com o conteudo da imagem do arquivo
*/

Pixel** get_image(FILE* img, Pixel ** newImg,int* height, int* width) {
    int i;
    int j;
    int fcount;
    int scount;
    int count;
    int dcc;
    char init[3];
    fscanf(img,"%s",init);

    if (init[0] == 'P' && init[1] == '3') 
    {
        fscanf(img,"%d %d",&j,&i);
        *width = j;
        *height = i;
        fscanf(img, "%d",&dcc);

        //Inicia alocacao dinamica

        newImg = (Pixel**) malloc(sizeof(Pixel*) * i);

        for ( count = 0; count < i ; ++count)
        {
            newImg[count] = (Pixel*) malloc(sizeof(Pixel) * j);
        }
        for (fcount = 0; fcount < i ; ++fcount)
        {
            for (scount = 0; scount < j; ++scount)
            {
                fscanf(img,"%i %i %i",&newImg[fcount][scount].r,&newImg[fcount][scount].g,&newImg[fcount][scount].b);
            }
        }
    }
    else
    {
        printf("Type of newFile not recognized\n");
    }

    fclose(img);

    return newImg;
}





