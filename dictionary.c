// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

bool is_loaded = false;
bool is_unloaded = false;
const unsigned int WORDS = 143091; // Number of words in the dictionary
#define TABLE_SIZE 143123  // A prime number slightly greater than 143,091

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = TABLE_SIZE;

// Hash table
node *table[TABLE_SIZE];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    unsigned int hash = 0;
    while (*word)
    {
        char c = tolower(*word);
        if (isalpha(c))
        {
            hash = (hash * 27 + (c - 'a' + 1)) % TABLE_SIZE; // 'a' is 1, 'b' is 2, ..., 'z' is 26, ' is 27.
        }
        else if (c == '\'')
        {
            hash = (hash * 27 + 27) % TABLE_SIZE; // Apostrophe is 27
        }
        word++;
    }
    return hash;

}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *file = fopen(dictionary, "r");
    if (!file)
    {
        return false;
    }

    char word[LENGTH + 1];
    while(fscanf(file, "%s", word) != EOF)
    {
        node *new_node = malloc(sizeof(node));
        if (!new_node)
        {
            unload();
            return false;
        }
        strcpy(new_node->word, word);
        unsigned int index = hash(word);
        new_node->next = table[index];
        table[index] = new_node;
    }
    fclose(file);
    is_loaded = true;
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    if (!is_loaded)
    {
        return 0;
    }
    else
    {
        WORDS;
    }
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        node *cursor = table[i];
        while(cursor)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    is_unloaded = true;
    return is_unloaded;
}
