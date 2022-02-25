#!/usr/bin/env python3
## Author: Anna Majewski
## Date: 24.02.2017
## Die Tuerme von Hanoi

from argparse import ArgumentParser
import sys, time

def hanoitowers(n, von, nach):
    if n==1:
        print("Lege die Scheibe von Stift {} auf Stift {}.".format(von, nach))
        return
    frei = 6 - von - nach
    hanoitowers(n-1, von, frei)
    print("Lege die Scheibe von Stift {} auf Stift {}.".format(von, nach))
    hanoitowers(n-1, frei, nach)
    return

def dauer(args):
    print("Wenn kein n angegeben wird, wird die Anleitung fuer einen Turm aus 4 Scheiben berechnet.")
    int(args.zahl)
    start = time.time()
    n = hanoitowers(args.zahl, args.von, args.nach)
    end = time.time()
    print("Dauer der Berechnung: {:.3} Sekunden".format(end-start))

parser = ArgumentParser()
parser.add_argument("-n", "--zahl", help="Die Anzahl der Scheiben.", type=int, default=4)
parser.add_argument("-f", "--von", help="Anfang des Turms", type=int, default=1)
parser.add_argument("-t", "--nach", help="Ende des Turms", type=int, default=3)
parser.set_defaults(func=dauer)
args = parser.parse_args()
args.func(args)