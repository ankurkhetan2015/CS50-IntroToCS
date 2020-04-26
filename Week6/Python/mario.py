from cs50 import get_int


def main():
    while True:
        print("Enter a positive number between 1 and 8 only.")
        height = get_int("Height: ")
        # checks for correct input condition
        if height >= 1 and height <= 8:
            break
    # call the function to implement the pyramid structure
    pyramid(height)


def pyramid(n):
    for i in range(n):
        # the loop that controls the blank spaces
        for j in range(n - 1 - i):
            print(" ", end="")
        # the loop that controls and prints the bricks
        for k in range(i + 1):
            print("#", end="")
        print("  ", end="")
        for l in range(i + 1):
            # the loop that control the second provided pyramid
            print("#", end="")
        # goes to the next pyramid level
        print()

main()


