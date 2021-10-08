#include "helpers.h"
#include <math.h>
#include <cs50.h>


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
     
    float red, green, blue, avg;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            red = image[i][j].rgbtRed;
            green = image[i][j].rgbtGreen;
            blue = image[i][j].rgbtBlue;
            avg = round((red + green + blue) / 3);
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    float sepiaRed, sepiaGreen, sepiaBlue;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sepiaRed = round(image[i][j].rgbtRed * .393 + image[i][j].rgbtGreen * .769 + image[i][j].rgbtBlue * .189);
            sepiaGreen = round(image[i][j].rgbtRed * .349 + image[i][j].rgbtGreen * .686 + image[i][j].rgbtBlue * .168);
            sepiaBlue = round(image[i][j].rgbtRed * .272 + image[i][j].rgbtGreen * .534 + image[i][j].rgbtBlue * .131);
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        int start = 0;
        int end = width - 1;
        RGBTRIPLE tmp;
        while (start < end)
        {
            tmp = image[i][start];
            image[i][start] = image[i][end];
            image[i][end] = tmp;
            start++;
            end--;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    float red, green, blue;
    RGBTRIPLE copiedImage[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copiedImage[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
           if (i == 0 && j == 0)
           {
               red = 0;
               green = 0;
               blue = 0;
               int count = 0;
               for (int a = 0; a <= 1; a++)
               {
                   for (int b = 0; b <= 1; b++)
                   {
                        red += copiedImage[a][b].rgbtRed;
                        green += copiedImage[a][b].rgbtGreen;
                        blue += copiedImage[a][b].rgbtBlue;
                        count++;
                   }
                }
                image[i][j].rgbtRed = round(red / count);
                image[i][j].rgbtGreen = round(green / count);
                image[i][j].rgbtBlue = round(blue / count);
           }
           else if (i == 0 && j == width - 1)
           {
                red = 0;
                green = 0;
                blue = 0;
                int count = 0;
                for (int a = 0; a <= 1; a++)
                {
                   for (int b = j - 1; b <= j; b++)
                   {
                        red += copiedImage[a][b].rgbtRed;
                        green += copiedImage[a][b].rgbtGreen;
                        blue += copiedImage[a][b].rgbtBlue;
                        count++;
                   }
                }
                image[i][j].rgbtRed = round(red / count);
                image[i][j].rgbtGreen = round(green / count);
                image[i][j].rgbtBlue = round(blue / count);
           }
           else if (i == height - 1 && j == 0)
           {
                red = 0;
                green = 0;
                blue = 0;
                int count = 0;
                for (int a = i - 1; a <= i; a++)
                {
                   for (int b = 0; b <= 1; b++)
                   {
                        red += copiedImage[a][b].rgbtRed;
                        green += copiedImage[a][b].rgbtGreen;
                        blue += copiedImage[a][b].rgbtBlue;
                        count++;
                   }
                }
                image[i][j].rgbtRed = round(red / 4);
                image[i][j].rgbtGreen = round(green / 4);
                image[i][j].rgbtBlue = round(blue / 4);
           }
           else if (i == height - 1 && j == width - 1)
           {
                red = 0;
                green = 0;
                blue = 0;
                int count = 0;
               for (int a = i - 1; a <= i; a++)
               {
                   for (int b = j - 1; b <= j; b++)
                   {
                        red += copiedImage[a][b].rgbtRed;
                        green += copiedImage[a][b].rgbtGreen;
                        blue += copiedImage[a][b].rgbtBlue;
                        count++;
                   }
               }
                image[i][j].rgbtRed = round(red / count);
                image[i][j].rgbtGreen = round(green / count);
                image[i][j].rgbtBlue = round(blue / count);
           }
           else if (i == 0 && j != 0 && j != width - 1)
           {
                red = 0;
                green = 0;
                blue = 0;
                int count = 0;
               for (int a = 0; a <= 1; a++)
               {
                   for (int b = j - 1; b <= j + 1; b++)
                   {
                        red += copiedImage[a][b].rgbtRed;
                        green += copiedImage[a][b].rgbtGreen;
                        blue += copiedImage[a][b].rgbtBlue;
                        count++;
                   }
               }
                image[i][j].rgbtRed = round(red / count);
                image[i][j].rgbtGreen = round(green / count);
                image[i][j].rgbtBlue = round(blue / count);
           }
           else if (i == height - 1 && j != 0 && j != width - 1)
           {
                red = 0;
                green = 0;
                blue = 0;
                int count = 0;
               for (int a = i - 1; a <= i; a++)
               {
                   for (int b = j - 1; b <= j + 1; b++)
                   {
                        red += copiedImage[a][b].rgbtRed;
                        green += copiedImage[a][b].rgbtGreen;
                        blue += copiedImage[a][b].rgbtBlue;
                        count++;
                   }
               }
                image[i][j].rgbtRed = round(red / count);
                image[i][j].rgbtGreen = round(green / count);
                image[i][j].rgbtBlue = round(blue / count);
           }
           else if (j == 0 && i != 0 && i != height - 1)
           {
                red = 0;
                green = 0;
                blue = 0;
                int count = 0;
               for (int a = i - 1; a <= i + 1; a++)
               {
                   for (int b = 0; b <= 1; b++)
                   {
                        red += copiedImage[a][b].rgbtRed;
                        green += copiedImage[a][b].rgbtGreen;
                        blue += copiedImage[a][b].rgbtBlue;
                        count++;
                   }
               }
                image[i][j].rgbtRed = round(red / 6);
                image[i][j].rgbtGreen = round(green / 6);
                image[i][j].rgbtBlue = round(blue / 6);
           }
           else if (j == width - 1 && i != 0 && i != height - 1)
           {
                red = 0;
               green = 0;
               blue = 0;
               int count = 0;
                for (int a = i - 1; a <= i + 1; a++)
               {
                   for (int b = j - 1; b <= j; b++)
                   {
                        red += copiedImage[a][b].rgbtRed;
                        green += copiedImage[a][b].rgbtGreen;
                        blue += copiedImage[a][b].rgbtBlue;
                        count++;
                   }
               }
                image[i][j].rgbtRed = round(red / count);
                image[i][j].rgbtGreen = round(green / count);
                image[i][j].rgbtBlue = round(blue / count);
           }
           else
           {
                red = 0;
               green = 0;
               blue = 0;
               int count = 0;
                for (int a = i - 1; a <= i + 1; a++)
                {
                    for (int b = j - 1; b <= j + 1; b++)
                    {
                        red += copiedImage[a][b].rgbtRed;
                        green += copiedImage[a][b].rgbtGreen;
                        blue += copiedImage[a][b].rgbtBlue;
                        count++;
                    }
                }
           
                image[i][j].rgbtRed = round(red / count);
                image[i][j].rgbtGreen = round(green / count);
                image[i][j].rgbtBlue = round(blue / count);
            }
        }
    }
    
    return;
}

bool is_corner(int i, int j, int height, int width)
{
    if ((i == 0 && j == 0) || (i == 0 && j == width - 1) || (i == height - 1 && j == 0) || (i == width - 1 && j == height - 1))
    {
        return true;
    }
    
    return false;
}

bool is_edge(int i, int j, int height, int width)
{
    if (is_corner(i, j, height, width) == false)
    {
        if (i == 0 || i == height - 1 || j == 0 || j == width - 1)
        {
            return true;
        }
    }   
    
    return false;
}

void cal_pixel(int i, int j, int height, int width)
{
    int i_start, j_start;
    int i_end, j_end;
    int count = 0;
    
    if (is_corner(i, j, height, width) == true) 
    {
        if (i == 0 && j == 0)
        {
            i_start = i;
            j_start = j;
        }
        else if (i == 0 && j == width - 1)
        {
            i_start = i;
            j_start = j - 1;
        }
        else if (i == height - 1 && j == 0)
        {
            i_start = i - 1;
            j_start = j;
        }
        else
        {
            i_start = i - 1;
            j_start = j - 1;
        }
        
        i_end = i_start + 1;
        j_end = j_start + 1;
    }
    else if is_edge(i, j, height, width) == true
    {
        
    }
}    