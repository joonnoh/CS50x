// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <cs50.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of words in dictionary
int wordCount = 0;

// If dictionary is loaded
bool loaded = false;

// Number of buckets in hash table
const unsigned int N = 75000;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    node *cursor = table[hash(word)];

    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        else
        {
            cursor = cursor->next;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned long hash = 5381;
    int c = *word;
    c = tolower(c);
    while (*word != 0)
    {
        hash = ((hash << 5) + hash) + c;
        c = *word++;
        c = tolower(c);
    }
    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    if (file != NULL)
    {
        char buffer[LENGTH + 1];
        int index;
        while (fscanf(file, "%s", buffer) != EOF)
        {
            node *n = malloc(sizeof(node));
            if (n != NULL)
            {
                strcpy(n->word, buffer);
                index = hash(n->word);
                n->next = table[index];
                table[index] = n;
                wordCount++;
            }
            else
            {
                printf("Cannot malloc node.\n");
                return false;
            }
        }
        fclose(file);
        loaded = true;
        return true;

    }
    else // File cannot be opened
    {
        printf("Could not open %s.\n", dictionary);
        return false;
    }
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    if (loaded)
    {
        return wordCount;
    }
    else
    {
        return 0;
    }
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    node *cursor;
    node *tmp;
    bool isFreed = false;

    for (int i = 0; i < N; i++)
    {
        cursor = table[i];

        while (cursor != NULL)
        {
            tmp = cursor;
            cursor = cursor->next;
            free(tmp);
            isFreed = true;
        }
    }

    return isFreed;
}
