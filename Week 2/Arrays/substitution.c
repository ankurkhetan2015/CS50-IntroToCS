#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

bool checkIfAlpha(char *alpha); //checks if the passed argument is a string with 26 different characters or not
void encryptSubstitution(string text, char *key); //applies the substitution cipher to encode the plaintext

int main(int argc, string argv[])
{
    char *key;
    string plaintext;

    bool checkAlpha;

    if (argc != 2) // checks for presence of two arguments including ./a.out
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else
    {
        char *alpha = argv[1];
        checkAlpha = checkIfAlpha(alpha);

        if (checkAlpha == false)
        {
            printf("Key must contain 26 distinguised alphabetic characters.\n");
            return 1;
        }
        else
        {
            key = argv[1]; //stores the passed string as required key
        }
    }

    plaintext = get_string("plaintext: "); //get the plaintext as user input
    encryptSubstitution(plaintext, key);

    return 0;
}

bool checkIfAlpha(char *alpha)
{
    int totalChar = 0, count[26] = {0}, temp;
    while (*alpha != '\0')
    {
        if (toupper(*alpha) < 'A' || toupper(*alpha) > 'Z') //checks for passed value as a alphabet character or not
        {
            return false;
        }
        else
        {
            temp = toupper(*alpha) - 'A';
            count[temp]++; //increases count for the index coressponding to characters with Aa as 0 and Zz as 25

        }
        alpha++;

    }

    for (int i = 0; i < 26; i++)
    {
        if (count[i] != 1) //checks if any character exists more than or less than one
        {
            return false;
        }
    }

    return true;
}

void encryptSubstitution(string text, char *key)
{
    int size = strlen(text);
    int encryptionIndex = 0, code = 0;

    printf("ciphertext: ");

    for (int i = 0; i < size; i++)
    {
        if (isupper(text[i])) //checks and supports condition for upper case
        {
            encryptionIndex = text[i] - 'A'; //calculates the index of a character in plaintext to encode
            code = toupper(*(key + encryptionIndex)); //replaces that character with corresponding key index

        }
        else if (islower(text[i])) //checks and supports condition for upper case
        {
            encryptionIndex = text[i] - 'a';
            code = tolower(*(key + encryptionIndex));
        }

        if (isalpha(text[i]))
        {
            printf("%c", code);
        }
        else
        {
            printf("%c", text[i]);
        }
    }
    printf("\n");
}