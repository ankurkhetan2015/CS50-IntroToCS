#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

bool checkIfDigit(char *digit); //checks if the passed argument is integer or not
void encryptCeasar(string text, int key); //applies the caesar cipher to encode the plaintext


int main(int argc, string argv[])
{
    int key;
    string plaintext;

    bool checkDigit;

    if (argc != 2) // checks for presence of two arguments including ./a.out
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    else
    {
        char *digit = argv[1];
        checkDigit = checkIfDigit(digit);

        if (checkDigit == false)
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
        else
        {
            key = atoi(argv[1]); //stores the passed string as required integer
        }
    }

    plaintext = get_string("plaintext: "); //get the plaintext as user input
    encryptCeasar(plaintext, key);

    return 0;
}

bool checkIfDigit(char *digit)
{
    while (*digit != '\0')
    {
        if (*digit < '0' || *digit > '9') //checks for passed value as a decimal or not
        {
            return false;
        }
        digit++;
    }

    return true;
}

void encryptCeasar(string text, int key)
{
    int size = strlen(text); //length of the plaintext
    int code;
    printf("ciphertext: ");

    if (key >= 26) //A + 27 is equivalent to B, so % 26 wraps around the alphabets
    {
        key = key % 26;
    }

    for (int i = 0; i < size; i++)
    {
        code = text[i] + key; //caesar cipher encryption

        //wrapping after Z or z
        if ((isupper(text[i])) && (code > 'Z'))
        {
            code -= 26;
        }
        else if (islower(text[i]) && (code > 'z'))
        {
            code -= 26;
        }
        //print the encoded alphabet or else just print any other character present in the plaintext
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
