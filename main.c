#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "filters.h"


int main(int argc, char const *argv[])
{
    //Declaracao de variaveis
    int height = 0, width = 0, effect = 0, times;
    int* pHeight, *pWidth;
    pHeight = &height;
    pWidth = &width;
    FILE* image;
    Pixel** newImg;
    Pixel** filteredImg;
    image = fopen(argv[1],"r");
    int casenum;
    char scase[3],ncase[3],rcase[10];


    newImg = get_image(image,newImg,pHeight,pWidth);
    image = fopen(argv[1],"r");
    filteredImg = get_image(image, filteredImg, pHeight, pWidth);
    //Menu em loop infinito
    while (effect== 0){
        printf("Filters:\nthr: Tresholding, blu: Blur, sha: Sharpen, edg: Edge detection\nTransformations:\nrot: Rotate, amp: Amplify, red: Reduce\nChoose an option: ");
        scanf("%s",scase);
        if (scase[0] == 't')
            {
            filteredImg = applyFilterTresholding(newImg, filteredImg, height, width);
            save_image("new_img.ppm",filteredImg,height,width);
            }
        else if (scase[0] == 'b')
            {
            filteredImg = applyFilterBlur(newImg, filteredImg, height, width);
            save_image("new_img.ppm",filteredImg,height,width);
            }
        else if(scase[0] == 's')
            {
            filteredImg = applyFilterSharpen(newImg, filteredImg, height, width);
            save_image("new_img.ppm",filteredImg,height,width);
            }
        else if(scase[0] == 'e')
            {
            filteredImg = edgeDetection(newImg, filteredImg, height, width);
            save_image("new_img.ppm",filteredImg,height,width);
            }
        else if(scase[0] == 'r' && scase[1] == 'e')
            {
            printf("In how many times? (2/ 4/ 8):\n");
            scanf("%i",&times);
            if (times == 2)
            	{
            	filteredImg = reduceImage(filteredImg, height, width, pHeight, pWidth);
            	}
            else if(times == 4)
            	{
            	filteredImg = reduceImage(filteredImg, height, width, pHeight, pWidth);
            	filteredImg = reduceImage(filteredImg, height, width, pHeight, pWidth);
            	}
            else if (times == 8)
            	{
            	filteredImg = reduceImage(filteredImg, height, width, pHeight, pWidth);
            	filteredImg = reduceImage(filteredImg, height, width, pHeight, pWidth);
            	filteredImg = reduceImage(filteredImg, height, width, pHeight, pWidth);
            	}
            else
            	{
            	break;
            	}
            save_image("new_img.ppm",filteredImg,height,width);
            }

        else if (scase[0] == 'a')
        	{
            printf("In how many times? (2/ 4/ 8):\n");
            scanf("%i",&times);
            if (times == 2)
            	{
            	filteredImg = amplifyImage(filteredImg, height, width, pHeight, pWidth);
                newImg = filteredImg;
            	}
            else if(times == 4)
            	{
            	filteredImg = amplifyImage(filteredImg, height, width, pHeight, pWidth);
            	filteredImg = amplifyImage(filteredImg, height, width, pHeight, pWidth);
                newImg = filteredImg;
            	}
            else if (times == 8)
            	{
            	filteredImg = amplifyImage(filteredImg, height, width, pHeight, pWidth);
            	filteredImg = amplifyImage(filteredImg, height, width, pHeight, pWidth);
            	filteredImg = amplifyImage(filteredImg, height, width, pHeight, pWidth);
                newImg = filteredImg;
            	}
            else
            	{
            	break;
            	}
            save_image("new_img.ppm",filteredImg,height,width);
        	}
        else if(scase[0] == 'r' && scase[1] == 'o'){
            printf("How would you like to rotate? (left, right or upside down)\n");
            scanf("%s",rcase);

            if(rcase[0] == 'r'){
                filteredImg = rotateImgRight(filteredImg, height, width);
                }
            else if(rcase[0] == 'l'){
                filteredImg = rotateImgLeft(filteredImg, height, width);
                }
            else if(rcase[0] == 'u'){
                filteredImg = rotateImgUpsideDown(filteredImg, height, width);
                }

            save_image("new_img.ppm",filteredImg, height, width);
        }
        else
            {
            printf("Invalid.\n");
            break;
            }

        while(1){
        	printf("would you like to do something else? y/n: ");
        	scanf("%s",ncase);
        	if (ncase[0] == 'n')
        	    {
        	    effect = 1;
        	    break;
        	    }
        	else if(ncase[0] == 'y')
        	    {
        	    break;
        	    }
        	else
           		{
           	 	printf("\n");
	        	}
        	}
    }
    return 0;
}
