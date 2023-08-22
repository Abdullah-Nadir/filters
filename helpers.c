#include <math.h>

#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterating through each row
    for (int i = 0; i < height; i++)
    {
        // Iterating through each column
        for (int j = 0; j < width; j++)
        {
            // Finding the average
            int average = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / (float) 3);

            // Assigning the same color
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterating through each row
    for (int i = 0; i < height; i++)
    {
        // Iterating through each column
        for (int j = 0; j < width / 2; j++)
        {
            // Creating a temporary variable
            RGBTRIPLE tempEle;

            // Assigning values to temporary variable
            tempEle.rgbtBlue = image[i][j].rgbtBlue;
            tempEle.rgbtGreen = image[i][j].rgbtGreen;
            tempEle.rgbtRed = image[i][j].rgbtRed;

            // Assigning values to the starting pixel's of image
            image[i][j].rgbtBlue = image[i][width - (j + 1)].rgbtBlue;
            image[i][j].rgbtGreen = image[i][width - (j + 1)].rgbtGreen;
            image[i][j].rgbtRed = image[i][width - (j + 1)].rgbtRed;

            // Assigning values to the ending pixel's of image
            image[i][width - (j + 1)].rgbtBlue = tempEle.rgbtBlue;
            image[i][width - (j + 1)].rgbtGreen = tempEle.rgbtGreen;
            image[i][width - (j + 1)].rgbtRed = tempEle.rgbtRed;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Copying the image
    RGBTRIPLE imgcpy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            imgcpy[i][j] = image[i][j];
        }
    }

    // Modifying pixels to create blurr effect
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Initializing variables for storing pixel's colours
            int blue, green, red;
            blue = green = red = 0;
            float counter = 0.00;

            // Accessing neighbouring pixels
            for (int k = -1; k < 2; k++)
            {
                int row = i + k;

                for (int l = -1; l < 2; l++)
                {
                    int col = j + l;

                    // Checking validity of the surrounding pixels
                    if (row >= 0 && row < height && col >= 0 && col < width)
                    {
                        blue += imgcpy[row][col].rgbtBlue;
                        green += imgcpy[row][col].rgbtGreen;
                        red += imgcpy[row][col].rgbtRed;
                        counter++;
                    }
                }
            }

            // Setting colours values of original values
            image[i][j].rgbtBlue = round(blue / counter);
            image[i][j].rgbtGreen = round(green / counter);
            image[i][j].rgbtRed = round(red / counter);
        }
    }

    return;
}

// helper function for checking if the resulting value is greater then 255
int max(long value)
{
    return value > 255 ? 255 : value;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Creating a copy of image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // Creating the kernals Gx and Gy
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // Accessing each pixdel for manipulation
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Initializing variables for computing weighted sum
            int gxRed = 0;
            int gyRed = 0;
            int gxGreen = 0;
            int gyGreen = 0;
            int gxBlue = 0;
            int gyBlue = 0;

            // Accessing neighbouring pixels
            for (int k = -1; k < 2; k++)
            {
                int neighbourRowIndex = i + k;
                int kernalRowIndex = 1 + k;

                for (int l = -1; l < 2; l++)
                {
                    int neighbourColIndex = j + l;
                    int kernalColIndex = 1 + l;

                    // Checking for valid neighbours
                    if (neighbourRowIndex >= 0 && neighbourRowIndex < height && neighbourColIndex >= 0 && neighbourColIndex < width)
                    {
                        gxRed += (copy[neighbourRowIndex][neighbourColIndex].rgbtRed * Gx[kernalRowIndex][kernalColIndex]);
                        gyRed += (copy[neighbourRowIndex][neighbourColIndex].rgbtRed * Gy[kernalRowIndex][kernalColIndex]);

                        gxGreen += (copy[neighbourRowIndex][neighbourColIndex].rgbtGreen * Gx[kernalRowIndex][kernalColIndex]);
                        gyGreen += (copy[neighbourRowIndex][neighbourColIndex].rgbtGreen * Gy[kernalRowIndex][kernalColIndex]);

                        gxBlue += (copy[neighbourRowIndex][neighbourColIndex].rgbtBlue * Gx[kernalRowIndex][kernalColIndex]);
                        gyBlue += (copy[neighbourRowIndex][neighbourColIndex].rgbtBlue * Gy[kernalRowIndex][kernalColIndex]);
                    }
                }
            }

            image[i][j].rgbtRed = max(round(sqrt(pow(gxRed, 2) + pow(gyRed, 2))));
            image[i][j].rgbtGreen = max(round(sqrt(pow(gxGreen, 2) + pow(gyGreen, 2))));
            image[i][j].rgbtBlue = max(round(sqrt(pow(gxBlue, 2) + pow(gyBlue, 2))));
        }
    }
}
