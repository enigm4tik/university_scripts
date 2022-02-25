#!/usr/bin/env python3
## Author: Anna Majewski
## Date: 27.02.2017-07.03.2017
## Description: Das Manhattan Tourist Problem
# mit Einlesen von Dateien, die die Kantengewichte enthalten

# Matrix mit horizontalen Gewichten: n*m-1
# Matrix mit vertikalen Gewichten: n-1*m
# Ergebnismatrix: n*m
import sys
if len(sys.argv) > 1:
    def manhattan(wd, wr, n, m):
        s = [[0 for col in range(m)] for row in range(n)]
        s[0][0] = 0
        for i in range(1, n):
            s[i][0] = s[i - 1][0] + wd[i - 1][0]
            # print("Durchgang", i, "Ergebnis s[",i, "][0]", s[i][0], "wd = ", wd[i-1][0])
        for j in range(1, m):
            s[0][j] = s[0][j - 1] + wr[0][j - 1]
            # print("Durchgang", j, "Ergebnis s[0][",j, "]", s[0][j], "wr = ", wr[0][j-1])
        for i in range(1, n):
            for j in range(1, m):
                a = s[i - 1][j] + wd[i - 1][j]
                # print("A ist ", a, "wd ist ", wd[i-1][j], "s ist ", s[i-1][j])
                b = s[i][j - 1] + wr[i][j - 1]
                # print("B ist ", b, "wr ist ", wr[i][j-1], "s ist ", s[i-1][j-2])
                s[i][j] = max(a, b)
                # print("Das Maximum von A und B ist ", s[i][j])
                ## if a == b:
                # speicher mir beides
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
            wd_string = line.split()
            wd_num = [float(x) for x in wd_string]
            wd.append(wd_num)

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
    ergebnis = manhattan(wd, wr, n, m)
    print("Ergebnismatrix: {} x {}\nEingabedatei: {}\nErgebnis: {}".format(n, m, sys.argv[1], ergebnis))
else:
    print("Eingabedatei fehlt.")