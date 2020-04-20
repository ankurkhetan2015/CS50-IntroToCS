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
            if ((image[i][j].rgbtBlue == image[i][j].rgbtGreen) && (image[i][j].rgbtBlue == image[i][j].rgbtRed))
            {
                continue;
            }
            avg_color = round(((float)image[i][j].rgbtBlue + (float)image[i][j].rgbtGreen + (float)image[i][j].rgbtRed) / 3);

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
    // min and max function takes care of corner and edge cases
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

    free(copyImage);
    return;
}
void sobelOperation(int currI, int currJ, int height, int width, RGBTRIPLE img[height][width], RGBTRIPLE neighbor[height][width],
                    int Gx[3][3], int Gy[3][3])
{
    // new value of each pixel would be average of values of all of pixels that are within 1 row and column of the original pixel
    int initialI = currI - 1;
    int initialJ = currJ - 1;

    int limitI = currI + 2;
    int limitJ = currJ + 2;

    //m and n are used to index Gx and Gy kernels
    int m = 0, n = 0;

    // to calculate the sum of all neighboring pixels according to their color, each color in pixel have separate Gx and Gy computation
    int16_t blue_Gx = 0, green_Gx = 0, red_Gx = 0;
    int16_t blue_Gy = 0, green_Gy = 0, red_Gy = 0;

    // each color has two values Gx and Gy but can only take one. Sobel operation formula to combine is sqrt(Gx^2 + Gy^2)
    double tempB = 0.0, tempG = 0.0, tempR = 0.0;

    for (int i = initialI; i < limitI; i++)
    {
        n = 0;
        for (int j = initialJ; j < limitJ; j++)
        {
            // assume 1 pixel solid black border around the edge of the image for ease of multiplication with Gx and Gy kernels, treat each color as 0
            if (i < 0 || i >= height || j < 0 || j >= width)
            {
                blue_Gx += 0 * Gx[m][n];
                green_Gx += 0 * Gx[m][n];
                red_Gx += 0 * Gx[m][n];

                blue_Gy += 0 * Gy[m][n];
                green_Gy += 0 * Gy[m][n];
                red_Gy += 0 * Gy[m][n];
            }

            // calculate the weighted sum for each color with each kernel
            else
            {
                blue_Gx += img[i][j].rgbtBlue * Gx[m][n];
                green_Gx += img[i][j].rgbtGreen * Gx[m][n];
                red_Gx += img[i][j].rgbtRed * Gx[m][n];

                blue_Gy += img[i][j].rgbtBlue * Gy[m][n];
                green_Gy += img[i][j].rgbtGreen * Gy[m][n];
                red_Gy += img[i][j].rgbtRed * Gy[m][n];
            }
            n++;
        }
        m++;
    }

    //combine the Gx and Gy for individual color in pixel using sobel operation formula
    tempB = round(sqrt(pow(blue_Gx, 2) + pow(blue_Gy, 2)));
    tempG = round(sqrt(pow(green_Gx, 2) + pow(green_Gy, 2)));
    tempR = round(sqrt(pow(red_Gx, 2) + pow(red_Gy, 2)));

    // capp the value at 255 if > than that
    if (tempB > 255)
    {
        tempB = 255;
    }
    if (tempG > 255)
    {
        tempG = 255;
    }
    if (tempR > 255)
    {
        tempR = 255;
    }

    // to store the weighted sum of all neighboring pixels at the address of copyImage
    neighbor[currI][currJ].rgbtBlue = tempB;
    neighbor[currI][currJ].rgbtGreen = tempG;
    neighbor[currI][currJ].rgbtRed = tempR;
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Sobel Operation matrix
    int Gx [3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy [3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // Created temporary struct to work with copy of image and then update original
    RGBTRIPLE(*copyImage)[width] = calloc(height, width * sizeof(RGBTRIPLE));

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sobelOperation(i, j, height, width, image, copyImage, Gx, Gy);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = copyImage[i][j].rgbtBlue;
            image[i][j].rgbtGreen = copyImage[i][j].rgbtGreen;
            image[i][j].rgbtRed = copyImage[i][j].rgbtRed;
        }
    }

    free(copyImage);
    return;
}