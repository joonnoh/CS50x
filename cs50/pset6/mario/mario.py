#!/usr/bin/env python3
# Print half pyramid from Mario
from cs50 import get_int

# Get pyramid height from user; must be between 1 and 8 inclusive
while True:
    height = get_int("Height: ")
    if height >= 1 and height <= 8:
        break

for i in range(1, height + 1):
    for j in range(height - i):
        print(" ", end="")
    for k in range(i):
        print("#", end="")
    print()