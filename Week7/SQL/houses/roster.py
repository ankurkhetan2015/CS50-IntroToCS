import csv
from sys import argv
import cs50

# Check if right number of arguments passed
if not len(argv) == 2:
    print("Usage: python import.py characters.csv")
    exit()

# Checks if correct house name is provided as command line argument, so initially false
correct = False

# Open students.db file for SQLite
db = cs50.SQL("sqlite:///students.db")

# Retrieve all possible house names from student table in database file students.db
houses = db.execute("SELECT DISTINCT(house) FROM students")

# Iterate over each house name and check if it matches the provided argument
for housename in houses:
    if argv[1] in housename['house']:
        # Update correct to indicate that right house name was provided
        correct = True
        break
# Exit the program with relevant error message if wrong argument passed
if correct == False:
    print("Enter the correct house name")
    exit()

# Query through student table to find student name, birth for provided house, order them by last name, if same then by first
students = db.execute("SELECT first, middle, last, birth FROM students WHERE house =? ORDER BY last ASC, first ASC", argv[1])

# Iterate over each student name for the given house
for student in students:
    # Store student's name in order, and also their birth year
    first = student['first']
    middle = student['middle']
    last = student['last']
    birth = student['birth']
    # If a student did or did not have middle name, print likewise (table returns value None for NULL(empty) fields)
    if middle == None:
        print(f"{first} {last}, born {birth}")
    else:
        print(f"{first} {middle} {last}, born {birth}")