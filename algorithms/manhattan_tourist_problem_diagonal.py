#!/usr/bin/env python3
## Author: enigm4tik
## Date: 10.04.2017-18.04.2017
## Manhattan Tourist Problem 03

## Description: Das Manhattan Tourist Problem
# mit Einlesen von Dateien, die die Kantengewichte enthalten
# zusaetzliche Werte fuer Diagonale.

# Matrix mit horizontalen Gewichten: n*m-1
# Matrix mit vertikalen Gewichten: n-1*m
# Ergebnismatrix: n*m
import sys
if len(sys.argv) > 1:
    def manhattan(wd, wr, wdia, n, m):
        s = [[0 for col in range(m)] for row in range(n)]
        s[0][0] = 0
        for i in range(1, n):
            s[i][0] = s[i - 1][0] + wd[i - 1][0]
        for j in range(1, m):
            s[0][j] = s[0][j - 1] + wr[0][j - 1]
        for i in range(1, n):
            for j in range(1, m):
                a = s[i - 1][j] + wd[i - 1][j] # weight_down
                b = s[i][j - 1] + wr[i][j - 1] # weight_right
                c = s[i-1][j-1] + wdia[i-1][j-1] # weight_diagonal
                s[i][j] = max(a, b, c) # max der drei werte!
        return s[n - 1][m - 1]

    ## zuerst count m / n
    # Zeilen zaehlen bei down = n-1
    # deshalb addiere ich beim letzten mal +1

    wd = []
    filename = sys.argv[1]
    file = open(filename)
    for line in file:
        if line.startswith("G_down"):
            count = 0
            continue
        elif line.startswith('---'):
            n = count + 1
            break
        else:
            count = count + 1
            # fuer m bei down = m, also muss man nichts dazugeben
            # m = laenge des strings der gespaltet werden kann
            m = len(line.split())
            wd_string = line.split() # string gesplittet
            wd_num = [float(x) for x in wd_string] # Zahl in float umgewandlet
            wd.append(wd_num) # zahl angefuegt

    #das selbe fuer die weights right
    file = open(filename)
    wr = []
    for line in file:
        if line.startswith("G_right"):
            for line in file:
                if line.startswith('---'):
                    break
                else:
                    wr_string = line.split()
                    wr_num = [float(y) for y in wr_string]
                    wr.append(wr_num)

    #das selbe fuer die Diagonale
    file = open(filename)
    wdia = []
    for line in file:
        if line.startswith("G_diag"):
            for line in file:
                if line.startswith('---'):
                    break
                else:
                    wdia_string = line.split()
                    wdia_num = [float(y) for y in wdia_string]
                    wdia.append(wdia_num)

    ergebnis = manhattan(wd, wr, wdia, n, m)
    print("Ergebnismatrix: {} x {}\nEingabedatei: {}\nErgebnis: {}".format(n, m, sys.argv[1], ergebnis))
else:
    print("Eingabedatei fehlt.")