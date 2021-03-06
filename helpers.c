#include "helpers.h"
#include <math.h>

/**
 * 1- The goal of this pset4 is to Implement a program that applies filters to BMPs
 * 2- Let's filter the image in "gray scale", "sepia", "refection" and "blur the image"
 * 3- Note that you can represent a bitmap as a two-dimensional array of pixels:
 * where the image is an array of lines, each line is an array of pixels, (this is how we chose to represent the bitmap images in this problem).
 */

// Convert image to grayscale
/* to convert a pixel to grayscale, we just need to make sure that the red, green and blue values are all the same */
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            float average = (image[row][col].rgbtBlue + image[row][col].rgbtRed + image[row][col].rgbtGreen) / 3.00;
            int avg = round(average);

            image[row][col].rgbtBlue = avg;
            image[row][col].rgbtRed = avg;
            image[row][col].rgbtGreen = avg;
        }
    }
    return;
}

// Convert image to sepia
/*
Base of values:
sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue
sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue
sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue
*/

void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            int sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            int sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);

            image[i][j].rgbtBlue = (sepiaBlue > 255) ? 255 : sepiaBlue;
            image[i][j].rgbtRed = (sepiaRed > 255) ? 255 : sepiaRed;
            image[i][j].rgbtGreen = (sepiaGreen > 255) ? 255 : sepiaGreen;
        }
    }
    return;
}

// Reflect image horizontally
/* all of the original pixels in the original image will still be present in the reflected image,
 * but those pixels may have been rearranged to be in a different location in the image. */

void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (width / 2); j++)
        {
            int red = image[i][j].rgbtRed;
            int blue = image[i][j].rgbtBlue;
            int green = image[i][j].rgbtGreen;

            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;

            image[i][width - j - 1].rgbtRed = red;
            image[i][width - j - 1].rgbtBlue = blue;
            image[i][width - j - 1].rgbtGreen = green;
        }
    }
    return;
}

// Blur image
/* we will use “box blur”, which works by taking each pixel and, for each color value,
 * giving it a new value by averaging the color values of the neighboring pixels. */

void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // temp is copy of image
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sumBlue = 0;
            int sumRed = 0;
            int sumGreen = 0;
            float counter = 0.00;

            for (int  k = -1; k < 2; k++)
            {
                for (int h = -1; h < 2; h++)
                {
                    if (i + k < 0 || i + k > height - 1 || j + h < 0 || j + h > width - 1)
                    {
                        continue;
                    }
                    sumBlue += image[i + k][j + h].rgbtBlue;
                    sumGreen += image[i + k][j + h].rgbtGreen;
                    sumRed += image[i + k][j + h].rgbtRed;

                    counter++;
                }
            }
            temp[i][j].rgbtBlue = round(sumBlue / counter);
            temp[i][j].rgbtRed = round(sumRed / counter);
            temp[i][j].rgbtGreen = round(sumGreen / counter);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
        }
    }
    return;
}
