#include <stdio.h>
#include <cs50.h>
int main(void)
{
    string name = get_string("What is your name?\n");
    // %s is a placeholder and whatever name that would be the user input, would go instead of it
    printf("hello, %s\n", name);
}
