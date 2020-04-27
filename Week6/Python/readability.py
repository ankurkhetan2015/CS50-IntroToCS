from cs50 import get_string


def main():

    # Initially word count is 1 as number of words are number of spaces plus 1
    sentenceCount = 0
    wordCount = 1
    letterCount = 0
    # Accepts user text to calculate its grade level
    text = get_string("Text: ")

    # Punctuations defined as end of sentence
    punctuations = ".!?"

    # For each character in given text, loop
    for letter in text:

        if letter in punctuations:
            sentenceCount += 1
        if letter == " ":
            wordCount += 1
        if letter.isalpha():
            letterCount += 1

    # Calculates letters per 100 words
    letterCount = (letterCount * 100) / wordCount
    # Calculates sentences per 100 words
    sentenceCount = (sentenceCount * 100) / wordCount
    # Coleman-Liau index based formula to calculate U.S. grade level
    gradeLevel = round(0.0588 * letterCount - 0.296 * sentenceCount - 15.8)

    # Special case: if grade level is under 1
    if gradeLevel < 1:
        print("Before Grade 1")
    # Special case: if grade level is equivalent to or greater than a senior undergraduate reading level
    elif gradeLevel >= 16:
        print("Grade 16+")
    # Prints the calculated grade level here
    else:
        print(f"Grade {gradeLevel}")


main()