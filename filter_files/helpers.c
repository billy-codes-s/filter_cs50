#include "helpers.h"
#include <stdint.h>
#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef uint16_t MEGABYTE;
MEGABYTE multiplicateur(MEGABYTE array[]);
BYTE finalaverage(BYTE arrayofcolor[]);
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // you have the numbers of total pixels (height *** width)
    /// you have the rgb value of each pixel... i think????
    ////you have the available memeory here, and each shit in memory

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            RGBTRIPLE buffer = image[i][j];
            int average_pre = round(((float)buffer.rgbtRed + (float)buffer.rgbtBlue+ (float)buffer.rgbtGreen)/3);
            buffer.rgbtRed = average_pre;
            buffer.rgbtBlue = average_pre;
            buffer.rgbtGreen = average_pre;
            image[i][j] = buffer;
            //done!
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{

    printf("%i", width);

    int rest = (width)%2;

    if(rest != 0)
        {
            printf("scenario 1");
            int noswitch1 = (width-1)/2;
            printf("%i\n", noswitch1);
            for (int i = 0; i < height; i++)
                {
                    for (int j =0; j < noswitch1; j++)
                    {
                        RGBTRIPLE buffer = image[i][width-j-1];
                        image[i][width-j-1] = image[i][j];
                        image[i][j] = buffer;

                    }
                }
        }

    if (rest == 0)
    {
        int noswitch = width/2;
        printf("%i\n", noswitch);
        printf("scenario 2");
        for (int i = 0; i < height; i++)
            {
                for (int j =0; j < noswitch; j++)
                    {
                        RGBTRIPLE buffer = image[i][width-j-1];
                        image[i][width-j-1] = image[i][j];
                        image[i][j] = buffer;

                    }

            }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE(*buff)[width] = calloc(height, width * sizeof(RGBTRIPLE));

    for (int i = 0; i < height; i++)
    {

        for (int j = 0; j < width; j++)
        {

            buff[i][j]= image[i][j];
        }

    }

    for (int i = 0; i < height; i++)
    {


        for (int j = 0; j < width; j++)
        {
            float total_red = 0;
            float total_blue = 0;
            float total_green = 0;
            int total_sur_pixel = 0;

            for(int x = i-1; x<i+2; x++)
            {
                if (x < 0)
                {
                    continue;
                }

                if (x >= height)
                {
                    continue;
                }

                for(int y = j-1; y<j+2; y++)
                {
                    if(y < 0)
                    {
                        continue;
                    }

                    if(y >= width)
                    {
                        continue;
                    }

                    total_red = total_red + buff[x][y].rgbtRed;
                    total_green  = total_green + buff[x][y].rgbtGreen;
                    total_blue = total_blue + buff[x][y].rgbtBlue;
                    total_sur_pixel++;

                }


            }
            image[i][j].rgbtRed = round(total_red/total_sur_pixel);
            image[i][j].rgbtBlue = round(total_blue/total_sur_pixel);
            image[i][j].rgbtGreen = round(total_green/total_sur_pixel);
        }

    }




}




// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE(*buff)[width] = calloc(height, width * sizeof(RGBTRIPLE));

    for (int i = 0; i < height; i++)
    {

        for (int j = 0; j < width; j++)
        {

            buff[i][j]= image[i][j];
        }

    }// verified by ramon



    MEGABYTE redarray[9];
    MEGABYTE bluearray[9];
    MEGABYTE greenarray[9];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int positions = 0;


            for (int k = i-1; k < i+2; k++)
            {
                for (int l = j-1; l < j+2; l++)
                {

                    if(k > height || k < 0 || l < 0|| l > width)
                    {
                       redarray[positions] = 0;
                       bluearray[positions] = 0;
                       greenarray[positions] = 0;
                       positions++;
                       continue;
                    }


                    redarray[positions] = buff[k][l].rgbtRed;
                    bluearray[positions] = buff[k][l].rgbtBlue;
                    greenarray[positions] = buff[k][l].rgbtGreen;
                    positions++;
                }
            }
        image[i][j].rgbtRed = multiplicateur(redarray);
        image[i][j].rgbtGreen = multiplicateur(greenarray);
        image[i][j].rgbtBlue = multiplicateur(bluearray);

        }
    }

    free(buff);
    return;
}

MEGABYTE multiplicateur(MEGABYTE array[])
{
    int total;
    total = -1*array[0] + 0*array[1] + 1*array[2] + -2*array[3] + 0*array[4] + 2*array[5] + -1*array[6] + 0*array[7] + 1*array[8];
    int total2;
    total2 = -1*array[0] + -2*array[1] + -1*array[2] + 0*array[3] + 0*array[4] + 0*array[5] + 1*array[6] + 2*array[7] + 1*array[8];
    int grandtotal = round(sqrt(total*total+total2*total2));

    if (grandtotal > 255)
    {
        grandtotal = 255;
    }
    MEGABYTE dung = grandtotal;
    return dung;

}
