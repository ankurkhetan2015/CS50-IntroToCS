// Implements a dictionary's functionality

#include <stdbool.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table (usually a prime number to minimize collisions)
const unsigned int N = 98317;

// Keep track of number of words in dictionary
int numWords = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Get index of searched word
    unsigned int index = hash(word);

    node *tmp = table[index];
    if (tmp == NULL) // Check if no node in table location
    {
        return false;
    }
    // If index in the hash table has some value
    while (tmp != NULL)
    {
        // Check if word searched is present in dictionary irrespective of case
        if (strcasecmp(tmp->word, word) == 0)
        {
            return true;
        }
        tmp = tmp->next;
    }

    return false;
}

/* Took ideas for hash function value (index) part and bucket size from mixture of following two sources

1. mrcrittall2016. “mrcrittall2016/CS50-pset5---Building-the-Fastest-Possible-Spell-Checker-in-C.” GitHub,
   github.com/mrcrittall2016/CS50-pset5---Building-the-fastest-possible-spell-checker-in-C/blob/master/dictionary.c.

2. Hash Table Dictionary -- Extra Credit, www.ccs.neu.edu/home/sbratus/com1101/hash-dict.html.
*/
// Hashes word to a number
unsigned int hash(const char *word)
{
    int i = 0;
    unsigned int value = 0;

    while (word[i] != '\0')
    {
        // newHash = (oneByte) ^ (oldHash << (shift 2 left));
        if (word[i] >= 65 && word[i] <= 90)
        {
            value = (word[i] + 32) ^ (value << 2); // Condition to evaluate same hash even if capital letters present
        }
        else
        {
            value = (word[i]) ^ (value << 2);
        }
        i++;
    }

    return (value % N);
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Open the dictionary file
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        unload();
        fclose(dict);
        printf("Could not open %s.\n", dictionary);
        return false;
    }

    unsigned int index = 0;
    // Loads a word from dictionary into loadword
    char loadword[LENGTH + 1];

    node *currword;
    int sizeNode = sizeof(node);

    // Keep scanning the dictionary till words are not exhausted
    while (fscanf(dict, "%s", loadword) != EOF)
    {
        // Create a new node for every word in dictionary
        currword = malloc(sizeNode);
        // Check if there is enough memory, then copy dictionary word in node
        if (currword != NULL)
        {
            strcpy(currword->word, loadword);
            currword->next = NULL;
        }
        else
        {
            return false;
        }
        // Find index where word will be stored in hashtable
        index = hash(currword->word);

        // Always insert at front
        if (table[index] == NULL)
        {
            table[index] = currword;
        }

        else
        {
            currword->next = table[index];
            table[index] = currword;
        }

        numWords++;
    }
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return numWords;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    node *temp = NULL;
    for (int i = 0; i < N; i++)
    {
        temp = table[i];
        for (node *current = table[i]; current != NULL; current = temp)
        {
            temp = temp->next;
            free(current);
        }
    }
    return true;
}
