#include <cs50.h>
#include <stdio.h>
#include <ctype.h>

void pyramid(int height);

int main(void)
{
    int height;
    do
    {
        printf("Enter a positive integer number between 1 and 8 only.\n");
        height = get_int("Height: "); //enter the positive height between 1 and 8 for pyramid
    }
    while ((height < 1) || (height > 8)); //checks for correct input condition

    pyramid(height); //call the function to implement the pyramid structure
}

void pyramid(int height)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = i + 1; j < height; j++) //the loop that controls the blank spaces
        {
            printf(" ");
        }
        for (int k = 0; k < i + 1; k++) //the loop that controls and prints the bricks("#")
        {
            printf("#");
        }
        printf("  ");
        for (int l = 0; l < i + 1; l++) //the loop that control the second provided pyramid
        {
            printf("#");
        }
        printf("\n"); //this print statement takes care of each next pyramid level
    }
}
