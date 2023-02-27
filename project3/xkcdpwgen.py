#!/usr/bin/env python3

# Eli Pinals kxkcd password gen

import argparse
import random

# set available characters
numbers = (["1", "2", "3", "4", "5", "6", "7", "8", "9", "0"])
symbols = (["~", "!", "@", "#", "$", "%", "^", "&", "*", ".", ":", ";"])

# PRINT THE PRETTY HELP MESSAGE
parsedArgs = argparse.ArgumentParser()
parsedArgs.add_argument('-w', '--words', type=int, default=4,
                    help='include WORDS words in the password (default=4)')
parsedArgs.add_argument('-c', '--caps', type=int, default=0,
                    help='capitalize the first letter of CAPS random words (default=0)')
parsedArgs.add_argument('-n', '--numbers', type=int, default=0,
                    help='insert NUMBERS random numbers in the password (default=0)')
parsedArgs.add_argument('-s', '--symbols', type=int, default=0,
                    help='insert SYMBOLS random symbols in the password (default=0)')
args = parsedArgs.parse_args()

# open, read, and split input file (words.txt)
words = open('words.txt').read().splitlines()

# initialize the password array
currentPass = []

# loop through arg words
for i in range(args.words):
    if (args.caps > 0):
        currentPass.append(random.choice(words).capitalize())
        args.caps -= 1
    else:
        currentPass.append(random.choice(words))

# loop through arg numbers
for i in range(args.numbers):
    currentPass.append(random.choice(numbers))

# loop through arg symbols
for i in range(args.symbols):
    currentPass.append(random.choice(symbols))

# shuffle the password elements
random.shuffle(currentPass)

# print the final password
print(currentPass)
