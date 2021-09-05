# Identify person's name whom a sequence of DNA belongs

import csv
import sys


def main():
    # Require command line arguments
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py csv txt")

    # Read CSV file into database list of dicts
    database = []
    largeFile = False
    with open(sys.argv[1]) as file:
        reader = csv.DictReader(file)
        for row in reader:
            # Check if CSV file contains additional STRs and flip largeFile to True
            if "TTTTTTCT" in row:
                largeFile = True
                db = {
                    "name": row["name"],
                    "AGATC": int(row.get("AGATC", 0)),
                    "TTTTTTCT": int(row.get("TTTTTTCT", 0)),
                    "AATG": int(row.get("AATG", 0)),
                    "TCTAG": int(row.get("TCTAG", 0)),
                    "GATA": int(row.get("GATA", 0)),
                    "TATC": int(row.get("TATC", 0)),
                    "GAAA": int(row.get("GAAA", 0)),
                    "TCTG": int(row.get("TCTG", 0))
                }
            else:
                db = {
                    "name": row["name"],
                    "AGATC": int(row.get("AGATC", 0)),
                    "AATG": int(row.get("AATG", 0)),
                    "TATC": int(row.get("TATC", 0))
                }

            database.append(db)

    # Read txt file into sequence string
    sequence = ""
    with open(sys.argv[2]) as file:
        reader = csv.reader(file)
        for row in reader:
            sequence = row[0]

    # Compute number of consecutive repeats for each STR in sequence
    countAGATC = consecutiveSTR(sequence, "AGATC")
    countAATG = consecutiveSTR(sequence, "AATG")
    countTATC = consecutiveSTR(sequence, "TATC")

    # If CSV file is large
    if largeFile:
        countTTTTTTCT = consecutiveSTR(sequence, "TTTTTTCT")
        countTCTAG = consecutiveSTR(sequence, "TCTAG")
        countGATA = consecutiveSTR(sequence, "GATA")
        countGAAA = consecutiveSTR(sequence, "GAAA")
        countTCTG = consecutiveSTR(sequence, "TCTG")
        for row in database:
            if (countAGATC == row["AGATC"] and countTTTTTTCT == row["TTTTTTCT"] and countAATG == row["AATG"] and countTCTAG == row["TCTAG"] and countGATA == row["GATA"] and countTATC == row["TATC"] and countGAAA == row["GAAA"] and countTCTG == row["TCTG"]):
                print(row["name"])
                sys.exit()
        print("No match")
    # If CSV file is small
    else:
        # Compare STR counts against each row in database
        for row in database:
            if (countAGATC == row["AGATC"] and countAATG == row["AATG"] and countTATC == row["TATC"]):
                print(row["name"])
                sys.exit()
        print("No match")


# Define functions for computing consecutive STRs
def consecutiveSTR(sequence, STR):
    count = 0
    s = STR
    while s in sequence:
        count += 1
        s += STR
    return count


# Call main function
if __name__ == "__main__":
    main()