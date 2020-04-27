from cs50 import get_float


def main():
    while True:
        amount = get_float("Change owed: ")
        # checks for correct input condition
        if amount >= 0.00:
            break
    # stores the equivalent dollar amount in cents
    changeDue = converttoCents(amount)
    # finds the minimum coins required to pay the amount owed
    minimumRequiredCoins(changeDue)


def converttoCents(amt):
    # returns the cents equivalent of the asked amount
    return round(amt * 100)


def minimumRequiredCoins(amt):
    # coins stores the individual cents that is required, totalCoins stores the minimum total coins needed
    totalCoins = 0

    while amt >= 5:

        if (amt // 25) > 0:
            coins = amt // 25
            amt -= coins * 25

        elif (amt // 10) > 0:
            coins = amt // 10
            amt -= coins * 10

        elif (amt // 5) > 0:
            coins = amt // 5
            amt -= coins * 5

        totalCoins += coins

    # adds all the remaining 1 cents needed
    totalCoins += amt

    print(f"{totalCoins}")


main()

