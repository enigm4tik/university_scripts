#!/usr/bin/env python3
## Author: Anna Majewski
## Date: 16.04.2017-19.04.2017
# Revision: 26.04.2017 - 19.05.2017
# Handling von ungleichlangen Sequenzen
# Ich habe mich entschieden den Pseudocode tatsaechlich so wie er in den Folien steht zu implementieren!
# Davor habe ich versucht meinen bisherigen Code (Diagonale) zu verwenden!

## Description: Needleman Wunsch Algorithmus mit 2 Sequenzen Revision

import sys

filename = "sequences.txt"

if len(sys.argv) > 1:
    filename = sys.argv[1]
    file_nw = open(filename)
    for line in file_nw:
        if line.startswith(">"):  # .fasta Format beginnt mit >
            continue  # da wir diese Zeile nicht wollen.
        else:
            s = line.strip()
            n = len(s)
        for line in file_nw:
            if line.startswith(">"):  # 2. Sequenz
                continue
            else:
                t = line.strip()
                m = len(t)

else:
    print("Keine Eingabedatei gewaehlt. \n"
          "Beim Aufruf bitte die Datei hinzuefuegen:\n"
          "'./Majewski_NW.py <filename>'\n\n"
          "Stattdessen wird mit default Sequenzen gerechnet.")
    s = 'GATCTATCAT'
    t = 'GACTATCATCAA'
    n = len(s)
    m = len(t)

# Gapkosten und Penaltykosten
gap = -2
penalty1 = 1
penalty2 = -1

def similarity(s, t):
    """Similarity Teil des Needleman Wunsch Algorithmus"""
    M = [[0 for i in range(m + 1)] for j in range(n + 1)]
    for i in range(0, n + 1):
        M[i][0] = i * gap
    for j in range(0, m + 1):
        M[0][j] = j * gap
    for i in range(1, n+1):
        for j in range(1, m+1):
            case1 = M[i - 1][j] + gap
            case2 = M[i][j - 1] + gap
            if s[i-1] == t[j-1]:
                penalty = 1
            elif s[i-1] != t[j-1]:
                penalty = -1
            case3 = M[i - 1][j - 1] + penalty
            M[i][j] = max(case1, case2, case3)
    return M

# Aufruf der Similarity Funktion
M = similarity(s, t)

# Instanzierung von leeren Listen
ausgabe_s = []
ausgabe_t = []

def align(i, j):
    """Backtracking Teil des Needleman Wunsch Algorithmus"""
    if i == 0 and j == 0:
        pass
    else:
        if M[i][j] == M[i-1][j] + gap:
            align(i-1, j)
            ausgabe_s.append(s[i-1])
            ausgabe_t.append('_')
        elif M[i][j] == M[i][j-1] + gap:
            align(i, j-1)
            ausgabe_s.append('_')
            ausgabe_t.append(t[j-1])
        elif M[i][j] == M[i-1][j-1] + penalty1 or M[i][j] == M[i-1][j-1] + penalty2:
            align(i-1, j-1)
            ausgabe_s.append(s[i-1])
            ausgabe_t.append(t[j-1])
    return (ausgabe_s, ausgabe_t)

ergebnis = align(n, m)

print('\nOptimales Sequenzalignment:\n'
      'Sequenz 1: {}\n'
      'Sequenz 2: {}\n'
      'Score: {}\n'
      'Alignment: \n'
      '{}\n{}'.format(s, t, M[n][m], ergebnis[0], ergebnis[1]))