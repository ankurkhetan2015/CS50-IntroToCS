#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

int *countInText(string text); //counts the number of letters, words and sentences in the provided text
int calculateReadability(int *count); //calculates the grade level based on Coleman-Liau index
void showGradeLevel(int gradeLevel); //prints the grade level according to its readability

int main(void)
{
    string text;
    int *countText; //a pointer to location that stores words, sentences and letters in this order
    int gradeLevel = 0;

    text = get_string("Text: "); //accepts user text to calculate its grade level

    countText = countInText(text);
    gradeLevel = calculateReadability(countText);
    showGradeLevel(gradeLevel);
}

int *countInText(string text)
{
    static int countText[3] = {1, 0, 0}; //{wordCount, sentenceCount, letterCount} ; initial word count is 1 as number of words are number of spaces plus 1

    for (int i = 0, size = strlen(text); i < size; i++)
    {
        if (text[i] == ' ') //checks if its a word
        {
            countText[0]++;
        }
        else if (text[i] == '.' || text[i] == '!' || text[i] == '?') //checks for a sentence
        {
            countText[1]++;
        }
        else if ((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z')) //checks for a letter
        {
            countText[2]++;
        }
    }

    return countText;
}

int calculateReadability(int *count)
{
    float wordCount = count[0];
    float sentenceCount = count[1];
    float letterCount = count[2];
    int grade = 0;

    letterCount = (letterCount * 100) / wordCount; //calculates letters per 100 words
    sentenceCount = (sentenceCount * 100) / wordCount; //calculates sentences per 100 words

    grade = round(0.0588 * letterCount - 0.296 * sentenceCount - 15.8); //Coleman-Liau index based formula to calculate U.S. grade level

    return grade;
}

void showGradeLevel(int gradeLevel)
{
    if (gradeLevel < 1) //special case: if grade level is under 1
    {
        printf("Before Grade 1\n");
    }
    else if (gradeLevel >= 16) //special case: if grade level is equivalent to or greater than a senior undergraduate reading level
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %d\n", gradeLevel); //prints the calculated grade level here
    }
}