# Calculate minimum number of coins required to give a user change

from cs50 import get_float

# Reprompt user until input is greater than zero
while True:
    change = get_float("Change owed: ") * 100
    if change > 0:
        break

quarters = dimes = nickels = pennies = 0

if change >= 25:
    quarters = int(change / 25)
    change = change % 25
if change >= 10:
    dimes = int(change / 10)
    change = change % 10
if change >= 5:
    nickels = int(change / 5)
    change = change % 5
if change >= 1:
    pennies = int(change / 1)
    change = change % 1

# Add up number of coins and print total
total = quarters + dimes + nickels + pennies

print(total)