#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculate the average of RGB and set each color to the value
            float average = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0;
            image[i][j].rgbtBlue = image[i][j].rgbtGreen = image[i][j].rgbtRed = (int)round(average);
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Use sepia algorithms for each color
            float sepiaRed = .393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue;
            float sepiaGreen = .349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue;
            float sepiaBlue = .272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue;
            // If result is greater than 255, set color to 255
            if (sepiaRed >= 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen >= 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue >= 255)
            {
                sepiaBlue = 255;
            }
            image[i][j].rgbtBlue = (int)round(sepiaBlue);
            image[i][j].rgbtGreen = (int)round(sepiaGreen);
            image[i][j].rgbtRed = (int)round(sepiaRed);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Copy reversed image to tmp
            tmp[i][width - j - 1] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Copy tmp to image
            image[i][j] = tmp[i][j];
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float rgbtBlueTotal = 0;
            float rgbtGreenTotal = 0;
            float rgbtRedTotal = 0;

            float rgbtBlueAvg;
            float rgbtGreenAvg;
            float rgbtRedAvg;

            if (i == 0 || i == height - 1 || j == 0 || j == width - 1) // If pixel is on edge
            {
                if (i == 0) // Top row of pixels
                {
                    if (j == 0) // Top left pixel
                    {
                        for (int r = 0; r <= 1; r++)
                        {
                            for (int c = 0; c <= 1; c++)
                            {
                                rgbtBlueTotal += image[i - r + 1][j - c + 1].rgbtBlue;
                                rgbtGreenTotal += image[i - r + 1][j - c + 1].rgbtGreen;
                                rgbtRedTotal += image[i - r + 1][j - c + 1].rgbtRed;
                            }
                        }

                        // Calculate color averages for 4 pixels
                        rgbtBlueAvg = (int)round(rgbtBlueTotal / 4.0);
                        rgbtGreenAvg = (int)round(rgbtGreenTotal / 4.0);
                        rgbtRedAvg = (int)round(rgbtRedTotal / 4.0);
                    }
                    else if (j == width - 1) // Top right pixel
                    {
                        for (int r = 0; r <= 1; r++)
                        {
                            for (int c = 0; c <= 1; c++)
                            {
                                rgbtBlueTotal += image[i - r + 1][j - c].rgbtBlue;
                                rgbtGreenTotal += image[i - r + 1][j - c].rgbtGreen;
                                rgbtRedTotal += image[i - r + 1][j - c].rgbtRed;
                            }
                        }

                        // Calculate color averages for 4 pixels
                        rgbtBlueAvg = (int)round(rgbtBlueTotal / 4.0);
                        rgbtGreenAvg = (int)round(rgbtGreenTotal / 4.0);
                        rgbtRedAvg = (int)round(rgbtRedTotal / 4.0);
                    }
                    else // All other top row pixels
                    {
                        for (int r = 0; r <= 1; r++)
                        {
                            for (int c = 0; c <= 2; c++)
                            {
                                rgbtBlueTotal += image[i - r + 1][j - c + 1].rgbtBlue;
                                rgbtGreenTotal += image[i - r + 1][j - c + 1].rgbtGreen;
                                rgbtRedTotal += image[i - r + 1][j - c + 1].rgbtRed;
                            }
                        }

                        // Calculate color averages for 6 pixels
                        rgbtBlueAvg = (int)round(rgbtBlueTotal / 6.0);
                        rgbtGreenAvg = (int)round(rgbtGreenTotal / 6.0);
                        rgbtRedAvg = (int)round(rgbtRedTotal / 6.0);
                    }
                }
                else if (i == height - 1) // Bottom row of pixels
                {
                    if (j == 0) // Bottom left pixel
                    {
                        for (int r = 0; r <= 1; r++)
                        {
                            for (int c = 0; c <= 1; c++)
                            {
                                rgbtBlueTotal += image[i - r][j - c + 1].rgbtBlue;
                                rgbtGreenTotal += image[i - r][j - c + 1].rgbtGreen;
                                rgbtRedTotal += image[i - r][j - c + 1].rgbtRed;
                            }
                        }

                        // Calculate color averages for 4 pixels
                        rgbtBlueAvg = (int)round(rgbtBlueTotal / 4.0);
                        rgbtGreenAvg = (int)round(rgbtGreenTotal / 4.0);
                        rgbtRedAvg = (int)round(rgbtRedTotal / 4.0);
                    }
                    else if (j == width - 1) // Bottom right pixel
                    {
                        for (int r = 0; r <= 1; r++)
                        {
                            for (int c = 0; c <= 1; c++)
                            {
                                rgbtBlueTotal += image[i - r][j - c].rgbtBlue;
                                rgbtGreenTotal += image[i - r][j - c].rgbtGreen;
                                rgbtRedTotal += image[i - r][j - c].rgbtRed;
                            }
                        }

                        // Calculate color averages for 4 pixels
                        rgbtBlueAvg = (int)round(rgbtBlueTotal / 4.0);
                        rgbtGreenAvg = (int)round(rgbtGreenTotal / 4.0);
                        rgbtRedAvg = (int)round(rgbtRedTotal / 4.0);
                    }
                    else // All other bottom row pixels
                    {
                        for (int r = 0; r <= 1; r++)
                        {
                            for (int c = 0; c <= 2; c++)
                            {
                                rgbtBlueTotal += image[i - r][j - c + 1].rgbtBlue;
                                rgbtGreenTotal += image[i - r][j - c + 1].rgbtGreen;
                                rgbtRedTotal += image[i - r][j - c + 1].rgbtRed;
                            }
                        }

                        // Calculate color averages for 6 pixels
                        rgbtBlueAvg = (int)round(rgbtBlueTotal / 6.0);
                        rgbtGreenAvg = (int)round(rgbtGreenTotal / 6.0);
                        rgbtRedAvg = (int)round(rgbtRedTotal / 6.0);
                    }
                }
                else if (j == 0) // Left column of pixels
                {
                    for (int r = 0; r <= 2; r++)
                    {
                        for (int c = 0; c <= 1; c++)
                        {
                            rgbtBlueTotal += image[i - r + 1][j - c + 1].rgbtBlue;
                            rgbtGreenTotal += image[i - r + 1][j - c + 1].rgbtGreen;
                            rgbtRedTotal += image[i - r + 1][j - c + 1].rgbtRed;
                        }
                    }

                    // Calculate color averages for 6 pixels
                    rgbtBlueAvg = (int)round(rgbtBlueTotal / 6.0);
                    rgbtGreenAvg = (int)round(rgbtGreenTotal / 6.0);
                    rgbtRedAvg = (int)round(rgbtRedTotal / 6.0);
                }
                else // Right column of pixels
                {
                    for (int r = 0; r <= 2; r++)
                    {
                        for (int c = 0; c <= 1; c++)
                        {
                            rgbtBlueTotal += image[i - r + 1][j - c].rgbtBlue;
                            rgbtGreenTotal += image[i - r + 1][j - c].rgbtGreen;
                            rgbtRedTotal += image[i - r + 1][j - c].rgbtRed;
                        }
                    }

                    // Calculate color averages for 6 pixels
                    rgbtBlueAvg = (int)round(rgbtBlueTotal / 6.0);
                    rgbtGreenAvg = (int)round(rgbtGreenTotal / 6.0);
                    rgbtRedAvg = (int)round(rgbtRedTotal / 6.0);
                }
            }

            else // Not edge pixel
            {

                for (int r = 0; r <= 2; r++)
                {
                    for (int c = 0; c <= 2; c++)
                    {
                        rgbtBlueTotal += image[i - r + 1][j - c + 1].rgbtBlue;
                        rgbtGreenTotal += image[i - r + 1][j - c + 1].rgbtGreen;
                        rgbtRedTotal += image[i - r + 1][j - c + 1].rgbtRed;
                    }
                }

                // Calculate color averages for 9 pixels
                rgbtBlueAvg = (int)round(rgbtBlueTotal / 9.0);
                rgbtGreenAvg = (int)round(rgbtGreenTotal / 9.0);
                rgbtRedAvg = (int)round(rgbtRedTotal / 9.0);

            }

            tmp[i][j].rgbtBlue = rgbtBlueAvg;
            tmp[i][j].rgbtGreen = rgbtGreenAvg;
            tmp[i][j].rgbtRed = rgbtRedAvg;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Copy tmp to image
            image[i][j] = tmp[i][j];
        }
    }

    return;
}
