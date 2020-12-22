#!/usr/bin/env python

import csv
import sys

if len(sys.argv) != 2:
    print('usage: {} filename'.format(sys.argv[0]))
    sys.exit(1)

with open(sys.argv[1], 'r', newline='') as csvfile:
    reader = csv.reader(csvfile)
    data = list(reader)
for line in zip(*data):
    print('|', ' | '.join(line), '|')
