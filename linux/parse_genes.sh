#! /bin/bash

## Date: 24.09.2016
## Author: enigm4tik
## Description: AWK Script um eine Datei zu parsen.

## Testlauf
#awk '{if ($3 == "gene"){print "hallo"}}' cbs7435.gff3

## AWK Script
# Anfang des Scripts: Ausgabe von "Beginne Parsen" und des Dateinamens.
awk 'BEGIN {print "Beginne Parsen von Datei " ARGV[1] "\n"}' cbs7435.gff3
# Das Script erkennt an Spalte 3 ob es sich um ein Gen handelt.
# Dann wird die letzte Spalte ($NF) in das Array attribute aufgespaltet, anhand des Trenners ";".
# Jedes dieser Arrayelemente wird noch einmal in ein Array data getrennt, anhand dem Zeichen "=".
# Danach folgt die Ausgabe data[1] "=>" data[2]. Die Schleife wird verlassen und das Trennzeichen wird ausgegeben "*********".
# Diese Ausgabe erfolgt in der Datei "ausgabe.txt".
awk '{if ($3 == "gene")
{ split($NF, attributes, ";");
for(i in attributes)
{split(attributes[i], data, "=");
print data[1] "=>" data[2];}
print "\n************ " }} ' cbs7435.gff3 >> ausgabe.txt
