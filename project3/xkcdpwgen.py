#!/usr/bin/env python3

import argparse
import random
import sys

parser = argparse.ArgumentParser()
parser.add_argument('-w', '--words', type=int, default=4,
help='include WORDS words in the password (default=4)')
parser.add_argument('-c', '--caps', type=int, default=0,
help='capitalize the first letter of CAPS random words (default=0)')
parser.add_argument('-n', '--numbers', type=int, default=0,
help='insert NUMBERS random numbers in the password (default=0)')
parser.add_argument('-s', '--symbols', type=int, default=0,
help='insert SYMBOLS random symbols in the password (default=0)')
args = parser.parse_args()

words = open('words.txt').read().splitlines()
numbers = (["0","1","2","3","4","5","6","7","8","9"])
symbols = (["~","!","@","#","$","%","^","&","*",".",":",";"])

pw_elements = []

for i in range(args.words):
    if (args.caps > 0):
        pw_elements.append(random.choice(words).capitalize())
        args.caps -= 1
    else:
        pw_elements.append(random.choice(words))

for i in range(args.numbers):
    pw_elements.append(random.choice(numbers))

for i in range(args.symbols):
    pw_elements.append(random.choice(symbols))

random.shuffle(pw_elements)

print("".join(pw_elements))