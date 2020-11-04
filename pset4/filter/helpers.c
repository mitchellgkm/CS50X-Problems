#include "helpers.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //To grayscale, the RGB values of a pixel simply become the average of all 3 -> 255 200 180 becomes X X X where X = (255 + 200 + 180) / 3
    for (int i = 0; i < height; i++) //Loop through height points
    {
        for (int j = 0; j < width; j++) //Loop through corresponding width points
        {
            //int *avg = malloc(sizeof(255)); //Allocate memory at location avg -> unneeded
            int avg = (int) round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0); //Average the 3 RGB values and place them in location avg -> Needs the 3.0 to be a float division and round properly

            image[i][j].rgbtBlue = avg; //Allocate the new average colour values to each pixel
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
            // free(avg); //Free up that memory
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{

    //To sepia, apply the sepia algorithm to each RGB value
    for (int i = 0; i < height; i++) //Loop through height points
    {
        for (int j = 0; j < width; j++) //Loop through corresponding width points
        {   //Apply sepia algorithm to each RGB value -> remember to round to nearest int and cap at 255
            int sRed = round((0.393 * image[i][j].rgbtRed) + (0.769 * image[i][j].rgbtGreen) + (0.189 * image[i][j].rgbtBlue)); 
            int sGreen = round((0.349 * image[i][j].rgbtRed) + (0.686 * image[i][j].rgbtGreen) + (0.168 * image[i][j].rgbtBlue));
            int sBlue = round((0.272 * image[i][j].rgbtRed) + (0.534 * image[i][j].rgbtGreen) + (0.131 * image[i][j].rgbtBlue));

            if (sBlue <= 255)
            {
                image[i][j].rgbtBlue = sBlue; //Allocate the new colour values to each pixel
            }
            else if (sBlue > 255)
            {
                image[i][j].rgbtBlue = 255;
            }

            if (sGreen <= 255)
            {
                image[i][j].rgbtGreen = sGreen; //Allocate the new colour values to each pixel
            }
            else if (sGreen > 255)
            {
                image[i][j].rgbtGreen = 255;
            }

            if (sRed <= 255)
            {
                image[i][j].rgbtRed = sRed; //Allocate the new colour values to each pixel
            }
            else if (sRed > 255)
            {
                image[i][j].rgbtRed = 255;
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //Any pixels on the left should end up on the right, and vice versa -> height doesn't need to be changed
    for (int i = 0; i < height; i++) //Loop through height points
    {
        for (int j = 0; j < width / 2; j++) //Loop through corresponding width points -> Only half as we want to flip at the mid-point
        {
            // RGBTRIPLE *x = &image[i][width - j];
            // RGBTRIPLE *y = malloc(sizeof(image[i][j]));

            // y = x;

            // free(y);

            int swap = width - 1 - j; //Last available pixel on the horizontal plane -> width of frame - 1

            RGBTRIPLE temp = image[i][j]; //Store current pixel in a temp variable
            image[i][j] = image[i][swap]; //Assign value of end pixel to current pixel
            image[i][swap] = temp; //Assign value of temp variable to end pixel
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width]; // create a temporary array to store a duplicate of image.
    // save a new copy of image as temp per color.
    for (int i = 0; i < height; i++) //Loop for height of image.
    {
        for (int j = 0; j < width; j++) //Loop for width of image and save color values in temp.
        {
            temp[i][j] = image[i][j]; //Don't want to access the blurred pixels -> we want each run to use original pixels
        }
    }

    for (int i = 0; i < height; i++) //Loop through height points
    {
        for (int j = 0; j < width; j++) //Loop through corresponding width points
        {
            int count = 1.0;

            int xRed = temp[i][j].rgbtRed;
            int xGreen = temp[i][j].rgbtGreen;
            int xBlue = temp[i][j].rgbtBlue;

            if (i > 0 && j > 0) //A
            {
                xRed += temp[i - 1][j - 1].rgbtRed;
                xGreen += temp[i - 1][j - 1].rgbtGreen;
                xBlue += temp[i - 1][j - 1].rgbtBlue;
                count++;
            }

            if (i > 0) //B
            {
                xRed += temp[i - 1][j].rgbtRed;
                xGreen += temp[i - 1][j].rgbtGreen;
                xBlue += temp[i - 1][j].rgbtBlue;
                count++;
            }

            if (i > 0 && j < width - 1) //C
            {
                xRed += temp[i - 1][j + 1].rgbtRed;
                xGreen += temp[i - 1][j + 1].rgbtGreen;
                xBlue += temp[i - 1][j + 1].rgbtBlue;
                count++;
            }

            if (j > 0) //D
            {
                xRed += temp[i][j - 1].rgbtRed;
                xGreen += temp[i][j - 1].rgbtGreen;
                xBlue += temp[i][j - 1].rgbtBlue;
                count++;
            }

            if (j < width - 1) //E
            {
                xRed += temp[i][j + 1].rgbtRed;
                xGreen += temp[i][j + 1].rgbtGreen;
                xBlue += temp[i][j + 1].rgbtBlue;
                count++;
            }

            if (i < height - 1 && j > 0) //F
            {
                xRed += temp[i + 1][j - 1].rgbtRed;
                xGreen += temp[i + 1][j - 1].rgbtGreen;
                xBlue += temp[i + 1][j - 1].rgbtBlue;
                count++;
            }

            if (i < height - 1) //G
            {
                xRed += temp[i + 1][j].rgbtRed;
                xGreen += temp[i + 1][j].rgbtGreen;
                xBlue += temp[i + 1][j].rgbtBlue;
                count++;
            }

            if (i < height - 1 && j < width - 1) //H
            {
                xRed += temp[i + 1][j + 1].rgbtRed;
                xGreen += temp[i + 1][j + 1].rgbtGreen;
                xBlue += temp[i + 1][j + 1].rgbtBlue;
                count++;
            }

            image[i][j].rgbtRed = round(xRed / (float) count);
            image[i][j].rgbtBlue = round(xBlue / (float) count);
            image[i][j].rgbtGreen = round(xGreen / (float) count);
        }
    }
    return;
}
