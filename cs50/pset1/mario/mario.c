// Problem Set 1: Mario Pyramid

#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompt for height
    int height;
    do
    {
        height = get_int("Height (1 thru 8): ");
    }
    while (height < 1 || height > 8);

    // Print pyramid
    for (int i = 1; i <= height; i++)
    {
        for (int k = height - i; k > 0; k--)
        {
            printf(" ");
        }

        for (int j = 0; j < i; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}