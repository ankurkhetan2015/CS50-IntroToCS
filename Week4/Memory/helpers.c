#include "helpers.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define max(x,y) ((x) >= (y)) ? (x) : (y)
#define min(x,y) ((x) <= (y)) ? (x) : (y)

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int avg_color; // calculates the average of red, green and blue for every pixel

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            avg_color = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3;

            // sets the original pixel with the new color set of RGB
            image[i][j].rgbtBlue = avg_color;
            image[i][j].rgbtGreen = avg_color;
            image[i][j].rgbtRed = avg_color;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int sepiaBlue, sepiaGreen, sepiaRed; // calculate and store new color based on given algorithm

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sepiaBlue = round(0.131 * image[i][j].rgbtBlue + 0.534 * image[i][j].rgbtGreen + 0.272 * image[i][j].rgbtRed);
            sepiaGreen = round(0.168 * image[i][j].rgbtBlue + 0.686 * image[i][j].rgbtGreen + 0.349 * image[i][j].rgbtRed);
            sepiaRed = round(0.189 * image[i][j].rgbtBlue + 0.769 * image[i][j].rgbtGreen + 0.393 * image[i][j].rgbtRed);

            // if resultant color is greater than 255, which is > maximum value for an 8-bit color value cap at 255
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }

            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }

            // sets the original pixel with the new color set of RGB
            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtRed = sepiaRed;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE swap; // to swap the pixels for a vertical flip (mirror reflection)

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++) // loop till midway of pixels as we can just swap [0][0] and [0][width - 1] and so on
        {
            swap = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = swap;
        }
    }
    return;
}

//logic behind neighbouring pixels taken from below
// Rooy, John La. “Determining Neighbours of Cell Two Dimensional List.” Stack Overflow, 25 Oct. 2009, stackoverflow.com/a/1621041.
void neighbors(int currI, int currJ, int height, int width, RGBTRIPLE img[height][width], RGBTRIPLE neighbor[height][width])
{
    // new value of each pixel would be average of values of all of pixels that are within 1 row and column of the original pixel
    int initialI = max(0, currI - 1);
    int initialJ = max(0, currJ - 1);

    int limitI = min(height, currI + 2);
    int limitJ = min(width, currJ + 2);

    // to calculate the total number of pixels under consideration
    float avg = 0.0;

    // to calculate the sum of all neighboring pixels according to their color, uint16_t otherwise would wrap around 255
    uint16_t blue = 0, green = 0, red = 0;

    for (int i = initialI; i < limitI; i++)
    {
        for (int j = initialJ; j < limitJ; j++)
        {
            blue += img[i][j].rgbtBlue;
            green += img[i][j].rgbtGreen;
            red += img[i][j].rgbtRed;
            avg++;

        }
    }

    // to store the average of all neighboring pixels at the address of copyImage
    neighbor[currI][currJ].rgbtBlue = round(blue / avg);
    neighbor[currI][currJ].rgbtGreen = round(green / avg);
    neighbor[currI][currJ].rgbtRed = round(red / avg);

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Created temporary struct to work with copy of image and then update original
    RGBTRIPLE(*copyImage)[width] = calloc(height, width * sizeof(RGBTRIPLE));

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            neighbors(i, j, height, width, image, copyImage); // checks and averages all neighboring pixel for each [i][j]
        }
    }

    // Update original image with new pixels calculated to blur
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = copyImage[i][j].rgbtBlue;
            image[i][j].rgbtGreen = copyImage[i][j].rgbtGreen;
            image[i][j].rgbtRed = copyImage[i][j].rgbtRed;
        }
    }

    return;
}

