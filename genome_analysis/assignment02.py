#! /usr/bin/env python3

import vcf

__author__ = 'enigm4tik'

class Assignment2:
    
    def __init__(self):
        ## Check if pyvcf is installed
        print("PyVCF version: %s" % vcf.VERSION, "\n")

        ## Dateiname in einer Variable
        self.filename = 'AmpliseqExome.20141120.NA24385.vcf'
        ## Öffnen mit vcf.Reader
        self.file = vcf.Reader(open(self.filename, 'r'))
        

    def get_average_quality_of_son(self):
        '''
        Get the average PHRED quality of all variants
        :return: average PHRED quality of all variants
        '''
        ## Die Summe und Anzahl wird initialisiert
        summe = 0
        anzahl = 0
        ## Danach wird für jeden Eintrag die Qualität bestimmt, addiert und die Anzahl um 1 erhöht
        for record in self.file:
            summe += record.QUAL
            anzahl += 1
        ## Am Schluss wird die Summe durch die Anzahl dividiert um den Durchschnitt zu berechnen
        average = summe/anzahl
        ## Das Ergebnis wird weitergegeben über return
        return average

        
    def get_total_number_of_variants_of_son(self):
        '''
        Get the total number of variants
        :return: total number of variants
        '''
        ## Öffnen der Datei mit dem vcf.Reader
        self.file = vcf.Reader(open(self.filename, 'r'))
        anzahl = 0
        ## Danach wird für jeden Eintrag die Qualität bestimmt, addiert und die Anzahl um 1 erhöht
        for record in self.file:
            anzahl += 1
        return anzahl

    def get_variant_caller_of_vcf(self):
        '''
        Return the variant caller name
        :return: Variant caller name
        '''
        ## Öffnen der Datei mit dem vcf.Reader
        self.file = vcf.Reader(open(self.filename, 'r'))
        ## Jede Zeile des Headers (_header_lines) wird durchsucht
        for line in self.file._header_lines:
            ## wenn die Zeile mit ##source beginnt, enthält sie die Info über den Caller
            ## das Format: ##source="tvc 4.5-1+0 (8ffe53a) - Torrent Variant Caller"
            if line.startswith('##source'):
                ## zuerst wird die erste Hälfte entfernt indem man die Zeile an " - " teilt
                caller = line.split(" - ")
                ## damit das Anführungszeichen am Ende entfernt wird, splite ich den String nochmal
                caller = caller[1].split("\"")
                ## beim Split wird eine Liste zurückgegeben deshalb verwende ich den 0. (1.) Eintrag.
        return caller[0]
        
    def get_human_reference_version(self):
        '''
        Return the genome reference version
        :return: genome reference version
        '''
        ## Öffnen der Datei mit dem vcf.Reader
        self.file = vcf.Reader(open(self.filename, 'r'))
        ## Jede Zeile des Headers (_header_lines) wird durchsucht
        for line in self.file._header_lines:
            ## wenn die Zeile mit ##reference beginnt, enthält sie die Info über den Caller
            ## aber da das öfter vorkommt, spezifiziere ich es zusätzlich
            ## das Format: ##reference=file:///results/referenceLibrary/tmap-f3/hg19/hg19.fasta
            if line.startswith('##reference=file://'):
                ## zuerst wird die zweite Hälfte entfernt indem man die Zeile an "." teilt
                version = line.split(".")
                ## damit man nur hg19 bekommt, splite ich den String nochmal
                version = version[0].split("/")
                ## beim Split wird eine Liste zurückgegeben deshalb verwende ich den 0. (1.) Eintrag.
        return version[7]
        
        
    def get_number_of_indels(self):
        '''
        Return the number of identified INDELs 
        :return: number of identified INDELs
        '''
        ## Anzahl der Indels initialisieren
        indels = 0
        ## Öffnen der Datei mit dem vcf.Reader
        self.file = vcf.Reader(open(self.filename, 'r'))
        ## pyvcf hat die Möglichkeit auf die indels zuzugreifen:
        ## record.is_indel ergibt true oder false
        ## https://pypi.python.org/pypi/PyVCF
        for record in self.file:
            if record.is_indel:
            ## Wenn es ein Indel ist, die Anzahl erhöhen
                indels += 1
        return indels

    def get_number_of_snvs(self):
        '''
        Return the number of SNVs
        :return: number of SNVs
        '''
        ## Anzahl der SNVs initialisieren
        snv = 0
        ## Öffnen der Datei mit dem vcf.Reader
        self.file = vcf.Reader(open(self.filename, 'r'))
        ## pyvcf hat die Möglichkeit auf snps zuzugreifen:
        ## record.is_snp ergibt true oder false
        ## https://pypi.python.org/pypi/PyVCF
        ## SNV und SNPs sind im Grunde das selbe, hängt nur davon ab ob es persönlich ist oder in einer Population gefunden wird.
        for record in self.file:
            if record.is_snp:
                ## Wenn es ein SNV/SNP ist, die Anzahl erhöhen
                snv += 1
        return snv
        
    def get_number_of_heterozygous_variants(self):
        '''
        Return the number of heterozygous variants
        :return: number of heterozygous variants
        '''
        ## Öffnen der Datei mit dem vcf.Reader
        self.file = vcf.Reader(open(self.filename, 'r'))
        ## Initialisieren der Variable Anzahl
        anz_het = 0
        ## pyvcf ermöglicht die Anzahl der homo-/hterozygoten Varianten zu bestimmen
        ## records.num_hets, records.num_hom_ref, record.num_hom_alt
        for record in self.file:
            ## wenn ein record eine heterozygote Variante ist, dann wird die Anzahl um 1 erhöht
            anz_het += record.num_het
        return anz_het
    
    def print_summary(self):
        ## Hier werden alle Methoden aufgerufen und mit einem String versehen, der beschreibt was sie ausgeben.
        print("Average Quality of Son:", self.get_average_quality_of_son())                         # 1753.7782222395415
        print("Total Number of Variants of Son:", self.get_total_number_of_variants_of_son())       # 38526
        print("Variant Caller:", self.get_variant_caller_of_vcf())                                  # Torrent Variant Caller
        print("Human Reference Version:", self.get_human_reference_version())                       # hg19
        print("Number of Indels:", self.get_number_of_indels())                                     # 1823
        print("Number of SNVs: ", self.get_number_of_snvs())                                        # 36703
        print("Number of heterozyous variants", self.get_number_of_heterozygous_variants())         # 23819
        
if __name__ == '__main__':
    print("Assignment 2")
    print("Author:", __author__, "\n")
    assignment1 = Assignment2()
    assignment1.print_summary()
    