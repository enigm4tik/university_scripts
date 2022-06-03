#!/usr/bin/env python3

## Author: enigm4tik
## Date: 24.02.2017
## Die Fibonacci Zahlen als rekursiver Algorithmus.

import time
from argparse import ArgumentParser

def recursion(n):
    if n ==1 or n == 2:
        return 1
    else:
        a = recursion(n-1)
        b = recursion(n-2)
    return a+b

def lookup(n):
    a = 1
    b = 1
    for i in range(2, n):
        erg = a+b
        a = b
        b = erg - a+b
    return erg

def vergleich(args):
    int(args.zahl)

    start = time.time()
    n = lookup(args.zahl)
    end = time.time()
    print("Wenn kein n angegeben wird, wird die 4. Fibonacci-Zahl berechnet.\nDas Ergebnis der Berechnung für die {}. Zahl lautet: {}". format(args.zahl, n))
    print("Dauer der Berechnung mit Iteration: {:.3} Sekunden".format(end-start))

    start = time.time()
    recursion(args.zahl)
    end = time.time()
    print("Dauer der Berechnung mit Rekursion: {:.3} Sekunden".format(end-start))

parser = ArgumentParser()
parser.add_argument("-n", "--zahl", help="Die nte Fibonacci Zahl.", type=int, default=4)
parser.set_defaults(func=vergleich)
args = parser.parse_args()
args.func(args)