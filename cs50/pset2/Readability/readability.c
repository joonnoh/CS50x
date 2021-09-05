// Problem Set 2: Readability
// Given text, compute the Coleman-Liau index reading grade level

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
int compute_index(int letters, int words, int sentences);

int main(void)
{
    // Get text from user
    string text = get_string("Text: ");

    // Count the number of letters, words, and sentences in text
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);

    // Compute grade level index
    int index = compute_index(letters, words, sentences);

    // Print results
    //printf("%i letters(s)\n", letters);
    //printf("%i word(s)\n", words);
    //printf("%i sentence(s)\n", sentences);

    // Print grade level index
    if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else // If grade level is between 1 and 15 inclusive
    {
        printf("Grade %i\n", index);
    }
}

// Function for counting number of letters in text
int count_letters(string text)
{
    int count = 0;

    // Iterate through text and count number of letters
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if ((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z'))
        {
            count++;
        }
    }

    return count;
}

// Function for counting number of words in text
int count_words(string text)
{
    // Assume at least one word in given text
    int count = 1;

    // Iterate through text and count number of spaces between each word
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == ' ')
        {
            count++;
        }
    }

    return count;
}

// Function for counting number of sentences in text
int count_sentences(string text)
{
    int count = 0;

    // Iterate through text and count number of ending puncutation
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            count++;
        }
    }

    return count;
}

// Function for computing Coleman-Liau index reading grade level
int compute_index(int letters, int words, int sentences)
{
    // Calculate L; average number of letters per 100 words in text
    float L = (float) letters * 100 / words;

    // Calculate S; average number of sentences per 100 words in text
    float S = (float) sentences * 100 / words;

    // Calculate index with Coleman-Liau formula
    float index = 0.0588 * L - 0.296 * S - 15.8;

    // Round index to nearest whole number for reading grade level
    int level = round(index);

    return level;
}