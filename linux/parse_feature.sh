#! /bin/bash

## Date: 24.09.2016
## Author: enigm4tik
## Description: Abgabe 2 - Shellskript zum Parsen von gff3 Dateien.

## Shellscript, das folgende Dinge können soll:
# 1 - einen Dateinamen als Parameter übergeben bekommen und testen
# ob ein Parameter übergeben wurde, wenn nicht dann Fehlerausgabe
# und Abbruch.

# -z bedeutet, nicht vorhanden. $1 ist der erste Parameter
# wenn kein Parameter angegeben wird, dann exit 1 (mit Error)
# Ein Dateiname wird als Parameter übergeben. 

if [[ -z $1 ]]; then
	echo "Kein Dateiname angegeben" >> log.txt
		exit 1
fi

# 2 eine Option übergeben (getopt) - wenn -o vorhanden, dann
# Programm-Output in eigene Datei, statt in STDOUT ausgeben

# ich übergebe die 2 Optionen n und o, die ausgewählt werden können
# wenn -o eingegeben wird, dann wird die Ausgabe in der übergebenen
# Datei eingegeben

ausgabe="/dev/stdout"

while getopts "o:" opt;
do
	case $opt in
		o) ausgabe="$OPTARG";;
	esac
done

#3 Fragen Sie den User, welchen Feature-Typ (gen, mRNA, etc.)
# er ausgewertet haben möchte. Usereingaben funktionieren mit
# dem Befehl 'read'. Übergeben Sie den entsprechenden Typ an
# das Skript im nächsten Punkt.

# Ich lese mit read das gewünschte Feature ein und speichere
# es in der Variable $feature.

read -p "Geben Sie das Feature ein: " feature

#4 Zeilenweises Einlesen der Eingabedatei: rufen Sie in dem
# Shell-Script das awk-Script von letzter Stunde auf, filtern
# Sie das Input-GFF entsprechend der Usereingabe und geben Sie
# das Ergebnis aus (STDOUT oder Datei).
# 4.1 Zählen Sie wieviele Features den Kriterien entsprechen
# und geben Sie die Summe am Ende des Skripts aus.

# Das awk Skript von letzter Woche wurde angepasst.
# Für $3 wird das feature verwenden, das zuerst an awk übergeben wird.
# Eine zusätzliche Variable durchlauf zum Zählen der Zeilen
# wird eingefügt.

awk -v feature="$feature" 'BEGIN {durchlauf=0; print "Beginne Parsen von Datei "ARGV[1] "\n"}
{if ($3 == feature)
{durchlauf+=1;
split($NF, attributes, ";");
for(i in attributes)
{split(attributes[i], data, "=");
print data[1] "=>" data[2];}
print "\n******************" }}
END {print "Es gab " durchlauf " Ergebnisse."} ' cbs7435.gff3 > $ausgabe

#5 Schreiben in ein Logfile, welches file wurde übergeben,
# was hat der User eingegeben, wieviele Zeilen entsprachen
# dem Kriterium, falls Fehler auftreten, diese ebenfalls 
# in das Logfile schreiben.

# Ich suche in der Spalte 3 meines Files nach dem $feature
# und speichere die Ausgabe des Wordcount in der Variable 
# $durchlauf. Ausgabe in der file: logfile.log
durchlauf=$(cut -f 3 cbs7435.gff3 | grep "$feature" | wc -l)

echo "Folgendes File wurde eingelesen: " $1 >> logfile.log
echo "Folgende Eingabe hat der User getippt: " $feature >> logfile.log
echo "Es gab folgende Anzahl an Ergebnissen: " $durchlauf >> logfile.log
echo "Folgende Fehler sind aufgetreten: " | 2>> logfile.log
