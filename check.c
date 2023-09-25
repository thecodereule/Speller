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
