// Problem Set 2: Caesar
// Encrypt messages using Caesar's cipher

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    // If program executed with more or less than one argument, print error message
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Exactly one argument
    else
    {
        // Return error if first char is '-' or '0'
        if (argv[1][0] == '-' || argv[1][0] == '0')
        {
            printf("Key must be positive integer\n");
            return 1;
        }

        else
        {
            // Check that each character in argument is a number
            for (int i = 0, n = strlen(argv[1]); i < n; i++)
            {
                // Return error if any char is not a digit
                if (!isdigit(argv[1][i]))
                {
                    printf("Key must be positive integer\n");
                    return 1;
                }
            }

            // Convert key string to integer
            int key = atoi(argv[1]);

            // Get plaintext from user
            string plaintext = get_string("plaintext: ");

            printf("ciphertext: ");

            // Iterate over plaintext and rotate each char
            for (int i = 0, n = strlen(plaintext); i < n; i++)
            {
                // If uppercase
                if (isupper(plaintext[i]))
                {
                    printf("%c", (plaintext[i] + key - 65) % 26 + 65);
                }

                // If lowercase
                else if (islower(plaintext[i]))
                {
                    printf("%c", (plaintext[i] + key - 97) % 26 + 97);
                }

                // If neither
                else
                {
                    printf("%c", plaintext[i]);
                }
            }

            // Print newline
            printf("\n");
        }

    }

}