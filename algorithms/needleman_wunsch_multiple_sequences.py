#!/usr/bin/env python3
## Author: enigm4tik
## Date: 24.04.2017 - 21.05.2017
## Description: Needleman Wunsch Algorithmus mit 3 Sequenzen
## Das Auffuellen der Matrix wird in 3 Schritten gemacht, damit keine Felder uebersehen werden.

import sys
import numpy

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
            for line in file_nw:
                if line.startswith(">"): # 3. Sequenz
                    continue
                else:
                    u = line.strip()
                    o = len(u)
else:
    print("Keine Eingabedatei gewaehlt. \n"
          "Beim Aufruf bitte die Datei hinzuefuegen:\n"
          "'./needleman_wunsch_multiple_sequences.py <filename>'\n\n"
          "Stattdessen wird mit default Sequenzen gerechnet.")
    s = 'GATCTATCAT'
    t = 'GACTATCATCAA'
    u = 'CATCATCATATAC'
    n = len(s)
    m = len(t)
    o = len(u)

# Gapkosten
gap = -5

def scoring(a, b):
    """Scoring Funktion für 2 Sequenzen"""
    if a == b:
        score = 2
        return score
    if a != b:
        score = -2
        return score

def scoring3(a, b, c):
    """Scoring Funktion für 3 Sequenzen"""
    if a == b:
        if b == c:
            score = 2 + 2
            return score
        elif b != c:
            score = 2 - 2
            return score
    if a == c:
        if a == b:
            score = 2 + 2
            return score
        if a != b:
            score = 2 - 2
            return score
    if a != b:
        if b == c:
            score = 2 - 2
            return score
        if b != c:
            score = - 2 - 2
            return score

def similarity(s, t, u):
    """Similarity Teil des Needleman Wunsch Algorithmus
    Diesmal angepasst, sodass auf 3 Sequenzen alignt wird.
    input: s, t, u = Sequenzen unterschiedlicher Länge
    return: Matrix mit den Scorewerten"""
    # Mit numpy kann man leichter Matrizen auffüllen.
    # Ohne numpy gab es Probleme beim Benutzen von unterschiedlich langen Sequenzen.

    M = numpy.zeros(shape=(n+1, m+1, o+1))

    ## Matrix mit Gapkosten auffüllen
    for i in range(0, n+1):
        M[i][0][0] = i * gap
    for j in range(0, m+1):
        M[0][j][0] = j * gap
    for k in range(0, o+1):
        M[0][0][k] = k * gap

    ## Auffuellen der Matrix beginnend bei 011
    for i in range(0, n+1):
        for j in range(1, m+1):
            for k in range(1, o+1):
                case1 = M[i-1][j][k] + gap
                case2 = M[i][j-1][k] + gap
                case3 = M[i][j][k-1] + gap
                case4 = M[i-1][j-1][k] + gap + scoring(s[i-1], t[j-1])
                case5 = M[i-1][j][k-1] + gap + scoring(s[i-1], u[k-1])
                case6 = M[i][j-1][k-1] + gap + scoring(t[j-1], u[k-1])
                case7 = M[i-1][j-1][k-1] + 1 + scoring3(s[i-1], t[j-1], u[k-1])
                M[i][j][k] = max(case1, case2, case3, case4, case5, case6, case7)

    ## Auffuellen der Matrix beginnend bei 101
    for i in range(1, n+1):
        for j in range(0, m+1):
            for k in range(1, o+1):
                case1 = M[i - 1][j][k] + gap
                case2 = M[i][j - 1][k] + gap
                case3 = M[i][j][k - 1] + gap
                case4 = M[i - 1][j - 1][k] + gap + scoring(s[i - 1], t[j - 1])
                case5 = M[i - 1][j][k - 1] + gap + scoring(s[i - 1], u[k - 1])
                case6 = M[i][j - 1][k - 1] + gap + scoring(t[j - 1], u[k - 1])
                case7 = M[i - 1][j - 1][k - 1] + 1 + scoring3(s[i - 1], t[j - 1], u[k - 1])
                M[i][j][k] = max(case1, case2, case3, case4, case5, case6, case7)

    ## Auffuellen der Matrix beginnend bei 110
    for i in range(1, n+1):
        for j in range(1, m+1):
            for k in range(0, o+1):
                case1 = M[i - 1][j][k] + gap
                case2 = M[i][j - 1][k] + gap
                case3 = M[i][j][k - 1] + gap
                case4 = M[i - 1][j - 1][k] + gap + scoring(s[i - 1], t[j - 1])
                case5 = M[i - 1][j][k - 1] + gap + scoring(s[i - 1], u[k - 1])
                case6 = M[i][j - 1][k - 1] + gap + scoring(t[j - 1], u[k - 1])
                case7 = M[i - 1][j - 1][k - 1] + 1 + scoring3(s[i - 1], t[j - 1], u[k - 1])
                M[i][j][k] = max(case1, case2, case3, case4, case5, case6, case7)
    return M

# Aufruf der Similarity Funktion
M = similarity(s, t, u)

# Instanzierung von leeren Listen
ausgabe_s = []
ausgabe_t = []
ausgabe_u = []

def align(i, j, k):
    """Backtracking Teil des Needleman Wunsch Algorithmus"""
    if i == 0 and j == 0 and k == 0:
        pass
    else:
        #case 1
        if M[i][j][k] == M[i-1][j][k] + gap:
            if i > 0:
                align(i-1, j, k)
                ausgabe_s.append(s[i-1])
                ausgabe_t.append('_')
                ausgabe_u.append('_')
            elif i == 0:
                align(i, j-1, k-1)
                ausgabe_s.append('_')
                ausgabe_t.append(t[j - 1])
                ausgabe_u.append(u[k - 1])
        #case 2
        elif M[i][j][k] == M[i][j-1][k] + gap:
            if j > 0:
                align(i, j-1, k)
                ausgabe_s.append('_')
                ausgabe_t.append(t[j-1])
                ausgabe_u.append('_')
            elif j == 0:
                align(i - 1, j, k - 1)
                ausgabe_s.append(s[i - 1])
                ausgabe_t.append('_')
                ausgabe_u.append(u[k - 1])
        #case 3
        elif M[i][j][k] == M[i][j][k-1] + gap:
            if k > 0:
                align(i, j, k-1)
                ausgabe_s.append('_')
                ausgabe_t.append('_')
                ausgabe_u.append(u[k-1])
            elif k == 0:
                align(i - 1, j - 1, k)
                ausgabe_s.append(s[i - 1])
                ausgabe_t.append(t[j - 1])
                ausgabe_u.append('_')
        #case 4
        elif M[i][j][k] == M[i-1][j-1][k] + gap + scoring(s[i-1], t[j-1]):
            if i > 0 and j > 0:
                align(i-1, j-1, k)
                ausgabe_s.append(s[i-1])
                ausgabe_t.append(t[j-1])
                ausgabe_u.append('_')
            elif i == 0:
                align(i, j-1, k-1)
                ausgabe_s.append('_')
                ausgabe_t.append(t[j - 1])
                ausgabe_u.append(u[k - 1])
            elif j == 0:
                align(i - 1, j, k - 1)
                ausgabe_s.append(s[i - 1])
                ausgabe_t.append('_')
                ausgabe_u.append(u[k - 1])
        #case 5
        elif M[i][j][k] == M[i-1][j][k-1] + gap + scoring(s[i-1], u[k-1]):
            if i > 0 and k > 0:
                align(i - 1, j, k -1)
                ausgabe_s.append(s[i-1])
                ausgabe_t.append('_')
                ausgabe_u.append(u[k-1])
            elif i == 0:
                align(i, j-1, k-1)
                ausgabe_s.append('_')
                ausgabe_t.append(t[j - 1])
                ausgabe_u.append(u[k - 1])
            elif k == 0:
                align(i - 1, j - 1, k)
                ausgabe_s.append(s[i - 1])
                ausgabe_t.append(t[j - 1])
                ausgabe_u.append('_')
        #case 6
        elif M[i][j][k] == M[i][j-1][k-1] + gap + scoring(t[j-1], u[k-1]):
            if j > 0 and k > 0:
                align(i, j - 1, k-1)
                ausgabe_s.append('_')
                ausgabe_t.append(t[j-1])
                ausgabe_u.append(u[k-1])
            elif j == 0:
                align(i - 1, j, k - 1)
                ausgabe_s.append(s[i - 1])
                ausgabe_t.append('_')
                ausgabe_u.append(u[k - 1])
            elif k == 0:
                align(i - 1, j - 1, k)
                ausgabe_s.append(s[i - 1])
                ausgabe_t.append(t[j - 1])
                ausgabe_u.append('_')
        #case 7
        elif M[i][j][k] == M[i-1][j-1][k-1] + 1 + scoring3(s[i-1], t[j-1], u[k-1]):
            if i > 0 and j > 0 and k > 0:
                align(i-1, j - 1, k-1)
                ausgabe_s.append(s[i-1])
                ausgabe_t.append(t[j-1])
                ausgabe_u.append(u[k-1])
            elif i == 0:
                align(i, j-1, k-1)
                ausgabe_s.append('_')
                ausgabe_t.append(t[j - 1])
                ausgabe_u.append(u[k - 1])
            elif j == 0:
                align(i-1, j, k - 1)
                ausgabe_s.append(s[i - 1])
                ausgabe_t.append('_')
                ausgabe_u.append(u[k - 1])
            elif k == 0:
                align(i-1, j - 1, k)
                ausgabe_s.append(s[i - 1])
                ausgabe_t.append(t[j - 1])
                ausgabe_u.append('_')
        else:
            if i > 0 and j > 0 and k > 0:
                align(i-1, j - 1, k-1)
                ausgabe_s.append(s[i-1])
                ausgabe_t.append(t[j-1])
                ausgabe_u.append(u[k-1])
            elif i == 0:
                if j > 0:
                    align(i, j-1, k)
                    ausgabe_s.append('_')
                    ausgabe_t.append(t[j - 1])
                    ausgabe_u.append('_')
                else:
                    if k > 0:
                        align(i, j, k-1)
                        ausgabe_s.append('_')
                        ausgabe_t.append('_')
                        ausgabe_u.append(u[k-1])
            elif j == 0:
                if i > 0:
                    align(i-1, j, k)
                    ausgabe_s.append(s[i - 1])
                    ausgabe_t.append('_')
                    ausgabe_u.append('_')
                else:
                    if k > 0:
                        align(i, j, k-1)
                        ausgabe_s.append('_')
                        ausgabe_t.append('_')
                        ausgabe_u.append(u[k - 1])
            elif k == 0:
                align(i-1, j - 1, k)
                ausgabe_s.append(s[i - 1])
                ausgabe_t.append(t[j - 1])
                ausgabe_u.append('_')

    return (ausgabe_s, ausgabe_t, ausgabe_u)

ergebnis = align(n, m, o)
print('\nOptimales Sequenzalignment:\n'
      'Sequenz 1: {}\n'
      'Sequenz 2: {}\n'
      'Sequenz 3: {}\n'
      'Score: {}\n'
      'Alignment: \n'
      '{}\n{}\n{}'.format(s, t, u, M[n][m][o], ergebnis[0], ergebnis[1], ergebnis[2]))