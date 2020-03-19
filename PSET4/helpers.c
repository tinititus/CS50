#include "helpers.h"
#include <math.h>
#include <stdarg.h>
#include <string.h>

// Function prototype
int average(int n, ...);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate over every pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Do the math using a float variable and round the operation
            //float mean = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);

            // Calculate the average the pixel's RGB values
            int mean = average(3, image[i][j].rgbtRed, image[i][j].rgbtGreen, image[i][j].rgbtBlue);
            // Assign the mean to the RGB values
            image[i][j].rgbtRed = mean;
            image[i][j].rgbtGreen = mean;
            image[i][j].rgbtBlue = mean;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;
    for (int i = 0; i < height; i++)
    {
        // Variables to iterate over the matrix's rows
        int m = 0;
        int n = width - 1;
        // Loops until every element has been swaped
        while (n > m)
        {
            // Auxiliary variable to swap
            temp = image[i][n];
            image[i][n] = image[i][m];
            image[i][m] = temp;
            m++;
            n--;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE image_copy[height][width];
    /*for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image_copy[i][j] = image[i][j];
        }
    }*/

    memcpy(image_copy, image, height * width * 3);

    for (int i = 0, red, green, blue, counter; i < height; i++)  // Add to the sum according to 9 cases to calc the avg
    {
        for (int j = 0; j < width; j++)
        {
            red = green = blue = counter = 0;

            // for any i, j add the own element's RGB values
            red += image_copy[i][j].rgbtRed;
            green += image_copy[i][j].rgbtGreen;
            blue += image_copy[i][j].rgbtBlue;
            counter++;  // Counter will be used to calculate the average in the end

            if ((j - 1) >= 0)  // if j >= 1 (1st col out) - or: if there is such a "(j - 1) neighbor"
            {
                red += image_copy[i][j - 1].rgbtRed;
                green += image_copy[i][j - 1].rgbtGreen;
                blue += image_copy[i][j - 1].rgbtBlue;
                counter++;
            }
            if ((j + 1) < width)  // if j < width - 1 (last col out)
            {
                red += image_copy[i][j + 1].rgbtRed;
                green += image_copy[i][j + 1].rgbtGreen;
                blue += image_copy[i][j + 1].rgbtBlue;
                counter++;
            }
            if ((i - 1) >= 0)  // if i >= 1 (1st row out)
            {
                red += image_copy[i - 1][j].rgbtRed;
                green += image_copy[i - 1][j].rgbtGreen;
                blue += image_copy[i - 1][j].rgbtBlue;
                counter++;
            }
            if ((i + 1) < height)  // if i < height - 1 (last row out)
            {
                red += image_copy[i + 1][j].rgbtRed;
                green += image_copy[i + 1][j].rgbtGreen;
                blue += image_copy[i + 1][j].rgbtBlue;
                counter++;
            }
            if ((i - 1) >= 0 && (j - 1) >= 0) // if i >= 1 && j >= 1 (1st row and col out)
            {
                red += image_copy[i - 1][j - 1].rgbtRed;
                green += image_copy[i - 1][j - 1].rgbtGreen;
                blue += image_copy[i - 1][j - 1].rgbtBlue;
                counter++;
            }
            if ((i - 1) >= 0 && (j + 1) < width)  // if i >= 1 && j < width - 1 (1st row and last col out)
            {
                red += image_copy[i - 1][j + 1].rgbtRed;
                green += image_copy[i - 1][j + 1].rgbtGreen;
                blue += image_copy[i - 1][j + 1].rgbtBlue;
                counter++;
            }
            if ((j - 1) >= 0 && (i + 1) < height)  // j >= 1 && i < height - 1 (first col and last row out)
            {
                red += image_copy[i + 1][j - 1].rgbtRed;
                green += image_copy[i + 1][j - 1].rgbtGreen;
                blue += image_copy[i + 1][j - 1].rgbtBlue;
                counter++;
            }
            if ((i + 1) < height && (j + 1) < width)  // i < height - 1 && j < width - 1 (last row and col out)
            {
                red += image_copy[i + 1][j + 1].rgbtRed;
                green += image_copy[i + 1][j + 1].rgbtGreen;
                blue += image_copy[i + 1][j + 1].rgbtBlue;
                counter++;
            }
            // Calculate the average for Red, Green, Blue values accordingly (with the help of 'counter')
            image[i][j].rgbtRed = round(red / (counter * 1.0));
            image[i][j].rgbtGreen = round(green / (counter * 1.0));
            image[i][j].rgbtBlue = round(blue / (counter * 1.0));
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate over G[i][j] to obtain Gx and swap indices to obtain Gy
    int G[3][3] = {{-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}

    };

    RGBTRIPLE image_copy[height][width];
    memcpy(image_copy, image, height * width * 3);

    for (int i = 0, Gxred, Gxgreen, Gxblue, Gyred, Gygreen, Gyblue; i < height;
         i++)
    {
        for (int j = 0; j < width; j++)
        {
            Gxred = Gxgreen = Gxblue = Gyred = Gygreen = Gyblue =  0;

            if ((j - 1) >= 0)  // if j >= 1 (1st col out) - or: if there is such a "(j - 1) neighbor"
            {
                Gxred += G[1][0] * image_copy[i][j - 1].rgbtRed;
                Gxgreen += G[1][0] * image_copy[i][j - 1].rgbtGreen;
                Gxblue += G[1][0] * image_copy[i][j - 1].rgbtBlue;
            }
            if ((j + 1) < width)  // if j < width - 1 (last col out)
            {
                Gxred += G[1][2] * image_copy[i][j + 1].rgbtRed;
                Gxgreen += G[1][2] * image_copy[i][j + 1].rgbtGreen;
                Gxblue += G[1][2] * image_copy[i][j + 1].rgbtBlue;
            }
            if ((i - 1) >= 0)  // if i >= 1 (1st row out)
            {
                Gyred += G[1][0] * image_copy[i - 1][j].rgbtRed;
                Gygreen += G[1][0] * image_copy[i - 1][j].rgbtGreen;
                Gyblue += G[1][0] * image_copy[i - 1][j].rgbtBlue;
            }
            if ((i + 1) < height)  // if i < height - 1 (last row out)
            {
                Gyred += G[1][2] * image_copy[i + 1][j].rgbtRed;
                Gygreen += G[1][2] * image_copy[i + 1][j].rgbtGreen;
                Gyblue += G[1][2] * image_copy[i + 1][j].rgbtBlue;
            }
            if ((i - 1) >= 0 && (j - 1) >= 0) // if i >= 1 && j >= 1 (1st row and col out)
            {
                Gxred += G[0][0] * image_copy[i - 1][j - 1].rgbtRed;
                Gxgreen += G[0][0] * image_copy[i - 1][j - 1].rgbtGreen;
                Gxblue += G[0][0] * image_copy[i - 1][j - 1].rgbtBlue;

                Gyred += G[0][0] * image_copy[i - 1][j - 1].rgbtRed;
                Gygreen += G[0][0] * image_copy[i - 1][j - 1].rgbtGreen;
                Gyblue += G[0][0] * image_copy[i - 1][j - 1].rgbtBlue;
            }
            if ((i - 1) >= 0 && (j + 1) < width)  // if i >= 1 && j < width - 1 (1st row and last col out)
            {
                Gxred += G[0][2] * image_copy[i - 1][j + 1].rgbtRed;
                Gxgreen += G[0][2] * image_copy[i - 1][j + 1].rgbtGreen;
                Gxblue += G[0][2] * image_copy[i - 1][j + 1].rgbtBlue;

                Gyred += G[2][0] * image_copy[i - 1][j + 1].rgbtRed;
                Gygreen += G[2][0] * image_copy[i - 1][j + 1].rgbtGreen;
                Gyblue += G[2][0] * image_copy[i - 1][j + 1].rgbtBlue;
            }
            if ((j - 1) >= 0 && (i + 1) < height)  // j >= 1 && i < height - 1 (first col and last row out)
            {
                Gxred += G[2][0] * image_copy[i + 1][j - 1].rgbtRed;
                Gxgreen += G[2][0] * image_copy[i + 1][j - 1].rgbtGreen;
                Gxblue += G[2][0] * image_copy[i + 1][j - 1].rgbtBlue;

                Gyred += G[0][2] * image_copy[i + 1][j - 1].rgbtRed;
                Gygreen += G[0][2] * image_copy[i + 1][j - 1].rgbtGreen;
                Gyblue += G[0][2] * image_copy[i + 1][j - 1].rgbtBlue;
            }
            if ((i + 1) < height && (j + 1) < width)  // i < height - 1 && j < width - 1 (last row and col out)
            {
                Gxred += G[2][2] * image_copy[i + 1][j + 1].rgbtRed;
                Gxgreen += G[2][2] * image_copy[i + 1][j + 1].rgbtGreen;
                Gxblue += G[2][2] * image_copy[i + 1][j + 1].rgbtBlue;

                Gyred += G[2][2] * image_copy[i + 1][j + 1].rgbtRed;
                Gygreen += G[2][2] * image_copy[i + 1][j + 1].rgbtGreen;
                Gyblue += G[2][2] * image_copy[i + 1][j + 1].rgbtBlue;
            }
            // Combine Gx and Gy for Red, Green, Blue values (Sobel filter)
            image[i][j].rgbtRed = fminf(round(sqrt(1.0 * (Gxred * Gxred + Gyred * Gyred))), 255.0);
            image[i][j].rgbtGreen = fminf(round(sqrt(1.0 * (Gxgreen * Gxgreen + Gygreen * Gygreen))), 255.0);
            image[i][j].rgbtBlue = fminf(round(sqrt(1.0 * (Gxblue * Gxblue + Gyblue * Gyblue))), 255.0);
        }
    }
    return;
}


// Calculates the average of n numbers
int average(int n, ...)
{
    int sum = 0;

    va_list ap;
    va_start(ap, n);

    for (int i = 0; i < n; i++)
    {
        sum += va_arg(ap, int);
    }

    va_end(ap);

    int average = (int) round(((float) sum) / n);

    return average;
}