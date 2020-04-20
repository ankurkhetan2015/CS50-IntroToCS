#include <stdio.h>
#include <cs50.h>
#include <math.h>

int numberofDigits(long number); //counts the number of digits present in the card number
int calculateSum(long number); //calculates the checksu value based on Luhn's algorithm
void checkValidity(long number); //checks for a cards validity and type

int main(void)
{
    long creditNum; //stores the credit card number
    creditNum = get_long("Enter your card number: ");

    checkValidity(creditNum);
}

int numberofDigits(long number)
{
    if (number == 0) //if only one digit in case of 0 as log of 0 is infinity and not handled by int type
    {
        return 1;
    }
    return (int)(log10(number) + 1); //log base 10 + 1 gives the digit count
}

int calculateSum(long number)
{
    int digit = 0, k = 1, sum = 0;
    while (number > 0)
    {
        digit = number % 10; //last digit of the present remaining number
        if (k % 2 == 0) //to evaluate only alternate digits starting from second-to-last digit
        {
            digit = digit * 2;
            if (numberofDigits(digit) == 1)
            {
                sum += digit;
            }
            else //if the prodcut with 2 gives a number that has more than 1 digit
            {
                while ((numberofDigits(digit) > 0) && (digit != 0))
                {
                    sum += digit % 10;
                    digit /= 10; 
                }
            }
        }
        else
        {
            sum += digit;
        }
        number /= 10;
        k++;
    }
    return sum;
}

void checkValidity(long number)
{
    int length = 0, checkSum = 0, startDigit = 0, firstDigit = 0; 
    
    length = numberofDigits(number);
    
    if (length < 13 || length > 16) //if the length of digits is beyond a valid card number
    {
        printf("INVALID\n");
    }
    else
    {
        checkSum = calculateSum(number);
    
        if ((checkSum % 10) != 0) //to check if card is syntactically vaild
        {
            printf("INVALID\n");
        }

        else
        {
            startDigit = (int)(number / pow(10, length - 2));
            firstDigit = (int)(number / pow(10, length - 1));

            if ((length == 15) && ((startDigit == 34) || (startDigit == 37))) //conditions for American express
            {
                printf("AMEX\n");
            }
            else if ((length == 16) && ((startDigit == 51) || (startDigit == 52) || (startDigit == 53) || (startDigit == 54)
                                        || (startDigit == 55))) //conditions for Mastercard
            {
                printf("MASTERCARD\n");
            }
            else if (((length == 13) || (length == 16)) && (firstDigit == 4)) //conditions for Visa
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
    }  
}
