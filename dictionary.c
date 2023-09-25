// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

bool is_loaded = false;
bool is_unloaded = false;
const unsigned int wordsInDict = 143091; // Number of words in the dictionary.txt
unsigned int matchedWords = 0;// Number of matched words
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
    // Convert the word to lowercase for case-insensitive comparison
    char lowercase_word[LENGTH + 1];
    int len = strlen(word);
    for (int i = 0; i < len; i++)
    {
        lowercase_word[i] = tolower(word[i]);
    }
    lowercase_word[len] = '\0'; // Null-terminate the lowercase word
    
    // Hash the word to get the index in the hash table
    unsigned int index = hash(lowercase_word);
    
    // Traverse the linked list at the computed index
    for (node *cursor = table[index]; cursor != NULL; cursor = cursor->next)
    {
        // Compare the word with the words in the dictionary
        if (strcmp(cursor->word, lowercase_word) == 0)
        {
            return true; // Word is in the dictionary
        }
    }
    return false; // Word is not in the dictionary
}


// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int hash = 0;
    while (*word) {
        char c = tolower(*word); // Convert to lowercase
        if (isalpha(c)) {
            hash = (hash * 27 + (c - 'a' + 1)) % TABLE_SIZE; // 'a' is 1, 'b' is 2, ..., 'z' is 26
        } else if (c == '\'') {
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
        matchedWords++;
    }
    fclose(file);
    is_loaded = true;
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return matchedWords;
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
