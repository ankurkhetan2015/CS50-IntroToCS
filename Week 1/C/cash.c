#include <stdio.h>
#include <cs50.h>
#include <math.h>

int convertToCents(float amount);
void minimumRequiredCoins(int changeDue);

int main(void)
{
    float amount; //stores the amount due to the customer
    
    do
    {
        amount = get_float("Change owed: ");
    }
    while (amount < 0.00); //checks for any invalid negative amount asked

    int changeDue = convertToCents(amount); //stores the equivalent dollar amount in cents
    minimumRequiredCoins(changeDue); //finds the minimum coins required to pay the amount owed
}

int convertToCents(float amount)
{
    return round(amount * 100); //returns the cents equivalent of the asked amount
}

void minimumRequiredCoins(int changeDue)
{
    //coins stores the individual cents that is required, totalCoins stores the minimum total coins needed
    int totalCoins = 0, coins = 0;

    while (changeDue >= 5)
    {
        if (changeDue / 25 > 0)
        {
            coins = changeDue / 25;
            changeDue -= coins * 25;
            totalCoins += coins;
        }
        else if (changeDue / 10 > 0)
        {
            coins = changeDue / 10;
            changeDue -= coins * 10;
            totalCoins += coins;
        }
        else if (changeDue / 5 > 0)
        {
            coins = changeDue / 5;
            changeDue -= coins * 5;
            totalCoins += coins;
        }
    }
    totalCoins += changeDue; //adds all the remaining 1 cents needed
    printf("%d\n", totalCoins);
}
