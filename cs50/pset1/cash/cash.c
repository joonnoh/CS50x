// Problem Set 1: Change in Coins

#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    // Prompt for change owed
    float change;
    do
    {
        change = get_float("Change owed: ");
    }
    while (change < 0);

    // Convert change to cents
    int cents = round(change * 100);

    // Calculate coins
    int quarters = 0;
    int dimes = 0;
    int nickels = 0;
    int pennies = 0;

    while (cents > 0)
    {
        while (cents >= 5)
        {
            while (cents >= 10)
            {
                while (cents >= 25)
                {
                    quarters = cents / 25;
                    cents = cents % 25;
                }

                dimes = cents / 10;
                cents = cents % 10;
            }

            nickels = cents / 5;
            cents = cents % 5;
        }

        pennies = cents / 1;
        cents = cents % 1;
    }

    // Add and print total number of coins
    int coins = quarters + dimes + nickels + pennies;
    printf("%i\n", coins);
}