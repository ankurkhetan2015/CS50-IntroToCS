import csv
from sys import argv
import cs50

# Check if right number of arguments passed
if not len(argv) == 2:
    print("Usage: python import.py characters.csv")
    exit()

# Open students.db file for SQLite
db = cs50.SQL("sqlite:///students.db")

# Delete all existing data from students table in students.db
db.execute("DELETE FROM students")

# Open characters.csv file to insert them into database
with open("characters.csv", 'r') as file:
    # Create DicReader
    reader = csv.DictReader(file)

    for row in reader:
        # Read all the csv file info into separate variables
        student = row["name"]
        house = row["house"]
        birth = row["birth"]

        # To handle name into "first middle last" format, split name on space
        student = student.split(' ')
        # Stores the first name of student
        first_name = student[0]

        # Counts the total number of words in name (2 if no middle name, 3 otherwise)
        words_name = len(student)
        if words_name == 2:
            # Last name of student is @ first index as no middle name
            last_name = student[1]
            # Insert rows in student table in students.db database file, place NULL value for middle name
            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, NULL, ?, ?, ?)",
                       first_name, last_name, house, birth)

        elif words_name == 3:
            # Middle name of student is @ first index which last name is now @ second (last) index
            middle_name = student[1]
            last_name = student[2]
            # Insert rows in student table in students.db database file, place proper middle name as provided
            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)",
                       first_name, middle_name, last_name, house, birth)