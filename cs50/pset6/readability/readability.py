# Compute approximate grade level needed to read text

from cs50 import get_string

# Get text input from user
text = get_string("Text: ")

# Initialize variables, assume one word if text is not empty
letters = words = sentences = 0

if len(text) > 0:
    words = 1

# Iterate through text
for c in text:
    if c.lower() >= 'a' and c.lower() <= 'z':
        letters += 1
    if c == " ":
        words += 1
    if c == '.' or c == '!' or c == '?':
        sentences += 1

# Calculate Coleman-Liau index
index = round(0.0588 * (letters * 100 / words) - 0.296 * (sentences * 100 / words) - 15.8)

# Print reading grade level
if index >= 16:
    print("Grade 16+")
elif index <= 1:
    print("Before Grade 1")
else:
    print(f"Grade {index}")