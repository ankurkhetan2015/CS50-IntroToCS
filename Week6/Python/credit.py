from cs50 import get_string
from sys import exit


def main():

    # Stores the credit card number as string
    creditNum = get_string("Enter your card number: ")

    # Checks for a cards validity and type
    checkValidity(creditNum)


def calculateSum(num):

    k = 1
    sum = 0
    while num > 0:
        # Last digit of the present remaining number
        digit = num % 10
        # To evaluate only alternate digits starting from second-to-last digit
        if k % 2 == 0:

            digit *= 2

            if len(str(digit)) == 1:
                sum += int(digit)

            # If the prodcut with 2 gives a number that has more than 1 digit
            else:

                while (len(str(digit)) > 0) and (not int(digit) == 0):
                    sum += digit % 10
                    digit //= 10
        else:
            sum += digit

        num //= 10
        k += 1
    return sum


def checkValidity(credit):

    # Stores the number of digits present in the card number
    numofDigits = len(credit)
    # Checks if the length of digits is beyond a valid card number
    if numofDigits < 13 or numofDigits > 16:
        print("INVALID")
        exit(1)

    # Calculates the checksum value based on Luhn's algorithm
    checkSum = calculateSum(int(credit))
    # Checks if card is syntactically vaild
    if not checkSum % 10 == 0:
        print("INVALID")
        exit(1)

    # According to provided conditions determine card type
    if numofDigits == 15 and credit[:2] in ["34", "37"]:
        print("AMEX")

    elif numofDigits == 16 and int(credit[:2]) in range(51, 56):
        print("MASTERCARD")

    elif numofDigits in [13, 16] and credit[:1] == "4":
        print("VISA")

    else:
        print("INVALID")


main()

