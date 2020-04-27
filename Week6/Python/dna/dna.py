import csv
from sys import argv

# Check if right number of arguments passed
if not len(argv) == 3:
    print("Usage: python dna.py data.csv sequence.txt")
    exit()

# Stores the database filename
database = argv[1]
# Stores the sequence filename
sequence = argv[2]

# Open the database file that has specific STR counts for multiple individuals
with open(database, 'r') as csv_file:

    reader = csv.DictReader(csv_file)

    # Stores the provided different types of STR for any individual
    listSTR = []
    for line in reader.fieldnames[1:]:
        listSTR.append(line)

    # Open the txt file containing the DNA sequence to identify
    with open(sequence, 'r') as dnafile:

        # Save the sequence as string
        dnadata = dnafile.readline()

        # Stores the count of all available STR in given order in database file
        listCount = []

        # Iterate over each STR one-by-one
        for givenSTR in listSTR:

            # Set initial max consecutive of a particular STR as 0
            max = 0
            # Stores length of given STR under consideration
            strLength = len(givenSTR)

            # Iterate over all characters in dna sequence string
            for i in range(len(dnadata)):

                # Set initial count for consecutive sequence as 0
                count = 0

                # Iterate and increment count till we find consecutive given STR
                while dnadata[i: i + strLength] == givenSTR:

                    count += 1
                    # Increase i to the location right after the end of current substring STR
                    i = i + strLength

                # If max consecutive for a particular STR is less than current consecutive STR found, update max
                if max < count:
                    max = count

                # Decrement i back to start from next search location since no STR found after last update of i
                i = i - strLength

            # Increment the total consecutive count of a given STR before looking up for next STR
            listCount.append(max)

    # Initially assume that no match found
    found = False

    # Loop through every individual's data
    for rows in reader:

        # Stores the stored information for any individual's STR
        databaseInfo = []
        for givenSTR in listSTR:
            databaseInfo.append(int(rows[givenSTR]))

        # If stored data matches given sequence data, match found and print individual's name
        if databaseInfo == listCount:
            found = True
            print(rows['name'])
            break
    # If no dna match was founs
    if found == False:
        print("No match")