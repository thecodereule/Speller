#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define TABLE_SIZE 143123  // Example table size, preferably a prime number

unsigned int radix_hash(const char *str) {
    unsigned int hash = 0;
    while (*str) {
        char c = tolower(*str); // Convert to lowercase
        if (isalpha(c)) {
            hash = (hash * 27 + (c - 'a' + 1)) % TABLE_SIZE; // 'a' is 1, 'b' is 2, ..., 'z' is 26
        } else if (c == '\'') {
            hash = (hash * 27 + 27) % TABLE_SIZE; // Apostrophe is 27
        }
        str++;
    }
    return hash;
}

int main() {
    const char *word = "a'b";
    unsigned int hash_value = radix_hash(word);
    printf("The hash value for %s is %u\n", word, hash_value);
    return 0;
}
