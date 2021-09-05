// Problem Set 1: Credit

#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    // Prompt for credit card number
    long number;
    do
    {
        number = get_long("Number: ");
    }
    while (number < 0);

    // Calculate checksum with Luhn's Algorithm
    long n = number;
    int d;
    int sum1 = 0;
    int sum2 = 0;
    int total;
    // Multiply every other digit by 2 starting with second-to-last digit and add those products' digits together
    // Also calculate sum of digits not multiplied by 2
    while (n > 0)
    {
        sum1 = sum1 + n % 10;
        n = n / 10;
        d = n % 10 * 2;
        sum2 = sum2 + (d % 10) + (d / 10 % 10);
        n = n / 10;
    }

    // Add sum of digits multiplied by 2 to sum of digits not multiplied
    total = sum1 + sum2;

    // If total's last digit is 0, then checksum passes
    if (total % 10 == 0)
    {
        // Calculate length of number
        int length = 0;
        long i = number;
        while (i > 0)
        {
            i = i / 10;
            length++;
        }

        // If number length is 13 digits long, check if Visa number if number starts with 4
        if (length == 13)
        {
            int start = number / 1000000000000 % 10;
            if (start == 4)
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        // If number is 15 digits long, check if American Express number if number starts with 34 or 37
        else if (length == 15)
        {
            int start = number / 10000000000000 % 100;
            if (start == 34 || start == 37)
            {
                printf("AMEX\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        // If number is 16 digits long, check if Visa if number starts with 4 or MasterCard number if number starts with 51, 52, 53, 54, or 55
        else if (length == 16)
        {
            int start = number / 1000000000000000 % 10;
            if (start == 4)
            {
                printf("VISA\n");
            }
            else
            {
                start = number / 100000000000000 % 100;
                if (start >= 51 && start <= 55)
                {
                    printf("MASTERCARD\n");
                }
                else
                {
                    printf("INVALID\n");
                }
            }
        }
        // Reject number if not 13, 15, or 16 digits long
        else
        {
            printf("INVALID\n");
        }
    }
    // If total's last digit is not 0, checksum fails and number invalid
    else
    {
        printf("INVALID\n");
    }
}