import mysql.connector
import pysam
import pybedtools

__author__ = 'enigm4tik'

## Allgemeine Information:
## Da mein Gen nicht auf Chromosom 11 liegt, aber wir mit dem BAM-File von Chromosom 11 arbeiten,
# habe ich mich entschieden den 11er bei den Funktionen hard zu coden:
# self.get_gene_reads_with_indels self.get_properly_paire d_reads_of_gene self.get_number_mapped_reads
# um zu testen ob das Programm "sinnvolle" Ergebnisse liefert.
# Mir ist bewusst, dass bei Eingabe meines Chromosoms (19) keine Ergebnisse erzielt werden koennen.


class Assignment1:
    
    def __init__(self):
        ## Your gene of interest
        self.gene = "B3GNT3" #B3GNT3
        ## Zuerst habe ich die Information in einer Zeile ausgelesen.
        # Da ich die Infos aber weiter verwenden will, schreibe ich sie in Variablen.
        # Die Namen der Spalten entnehme ich der SQL-query.
        # Diese werden beim Ausfuehren des Query aufgefuellt.
        self.info = []
        self.name = ""
        self.chrom = ""
        self.txStart = ""
        self.txEnd = ""
        self.strand = ""
        self.exonCount = ""
        self.exonStarts = ""
        self.exonEnds = ""

    def fetch_gene_coordinates(self, genome_reference, file_name):
        '''Diese Methode verbindet sich zu UCSC und holt dort Daten
        :return nothing'''
        
        print ("Connecting to UCSC to fetch data")
        
        ## Open connection
        cnx = mysql.connector.connect(host='genome-mysql.cse.ucsc.edu', user='genomep', passwd='password', db=genome_reference)
        
        ## Get cursor
        cursor = cnx.cursor()
        
        ## Build query fields
        query_fields = ["refGene.name2",
                        "refGene.name",
                        "refGene.chrom",
                        "refGene.txStart",
                        "refGene.txEnd",
                        "refGene.strand",
                        "refGene.exonCount",
                        "refGene.exonStarts",
                        "refGene.exonEnds"]
        
        ## Build query
        query = "SELECT DISTINCT %s from refGene" % ",".join(query_fields)
        
        ## Execute query
        ergebnis = cursor.execute(query)
        
        ## Write to file
        with open(file_name, "w") as fh:
            for row in cursor:
                fh.write(str(row) + "\n")
                ## Wenn mein Gen erkannt wird, werden die Informationen in ein Tupel "row" geschrieben
                if row[0] == self.gene:
                    info = row
                    ## Dieses tupel loese ich so auf, dass jeder Teil der Info in einer Variable gespeichert wird.
                    self.gene = info[0]
                    self.name = info[1]
                    self.chrom = info[2]
                    self.txStart = info[3]
                    self.txEnd = info[4]
                    self.strand = info[5]
                    self.exonCount = info[6]
                    self.exonStarts = info[7] # Das ist ein bytestring
                    self.exonEnds = info[8] # Das ist ein bytestring

        ## Close cursor & connection
        cursor.close()
        cnx.close()
        
        print ("Done fetching data")
                
    def get_sam_header(self):
        '''Diese Methode holt den SAM Header aus dem BAM File
        :return Version, Sorting order of alignments, grouping of alignments'''
        # Um ein BAM file lesen zu koennen muss man ein alignmentfile object erstellen
        path_to_file = '/home/taka/medgen/HG00096.chrom11.ILLUMINA.bwa.GBR.low_coverage.20120522.bam'
        samfile = pysam.AlignmentFile(path_to_file, "rb")
        # laut manual enthaelt das first level "HD" oder "SQ".
        # in HD steht: VN = Format Version und SO = Sorting order of alignments
        # zusaetzlich noch GO = grouping of alignments

        # uns interessiert der header, deshalb
        for header, item in samfile.header['HD'].items():
            if header == 'VN':
                print ("Version: {}".format(item))
            if header == 'SO':
                print("Sorting order of alignments: {}".format(item))
            if header == 'GO':
                print("Grouping of alignments: {}".format(item))

        samfile.close()
        
    def get_properly_paired_reads_of_gene(self):
        '''Diese Methode zaehlt die proper reads oder gibt sie aus.
        :return anzahl der properly paired reads'''

        ## diese Methode funktioniert nur mit indizierten BAM Files
        ## deshalb wurde in der Konsole (ausserhalb dieses Programms) die Datei indiziert:
        ## taka@Yurnero:~/medgen/assignment01$ samtools index HG00096.chrom11.ILLUMINA.bwa.GBR.low_coverage.20120522.bam

        ## samfile wird wieder geoeffnet
        path_to_file = '/home/taka/medgen/assignment01/HG00096.chrom11.ILLUMINA.bwa.GBR.low_coverage.20120522.bam'
        samfile = pysam.AlignmentFile(path_to_file, "rb")
        anzahl = 0
        ## 11 steht fuer Chromosom 11 und txStart bzw. Ende geben an, wo mein Gen sich befindet
        for read in samfile.fetch("11", self.txStart, self.txEnd):
            if read.is_proper_pair:
                anzahl += 1
        ## da sehr viele (908) Reads properly paired sind und die gesamte Zeile dafuer ausgegeben wird,
        ## habe ich mich entschieden die Anzahl der properly paired reads auszugeben.
        ## wenn gewuenscht ist, dass die reads per se ausgegeben werden, einfach in der folgenden Zeile das # entfernen.

                #print(read)

        samfile.close()
        return anzahl
        
    def get_gene_reads_with_indels(self):
        '''Diese Methode zaehlt wieviele der Reads in meinem Gen Indels haben.
        :return anzahl der reads mit indels'''

        ## Indels kann man im CIGAR String finden:
        ##https: // samtools.github.io / hts - specs / SAMv1.pdf
        ## wenn ein D oder ein I im CIGAR String vorhanden ist, hat man ein INDEL gefunden.
        ## der CIGAR String befindet sich in der 6. Spalte = index 5

        ## samfile wird wieder geoeffnet
        path_to_file = '/home/taka/medgen/assignment01/HG00096.chrom11.ILLUMINA.bwa.GBR.low_coverage.20120522.bam'
        samfile = pysam.AlignmentFile(path_to_file, "rb")
        anzahl = 0

        ## 11 steht fuer Chromosom 11 und txStart bzw. Ende geben an, wo mein Gen sich befindet
        for read in samfile.fetch("11", self.txStart, self.txEnd):
            if not read.is_unmapped:
                cigar = read.cigar
                for typ, vorkommen in cigar:
                    if typ == 1 or typ == 2:
                        anzahl += 1

            ## Wenn statt der Anzahl die Zeile gewuenscht ist, einfach # entfernen:

                #print(read)

        samfile.close()
        return anzahl
        
    def calculate_total_average_coverage(self):
        '''Diese Methode berechnet die Coverage des bam-files.
        :return average coverage des files.'''

        ## pybedtools empfiehlt die a, b Nomenklatur fuer die Berechnung

        a = pybedtools.BedTool('HG00096.chrom11.ILLUMINA.bwa.GBR.low_coverage.20120522.bam')
        b = a.genome_coverage(bg=True)

        anzahl = 0
        coverage = 0

        for line in b:
            ## in jeder Zeile die coverage auslesen und die Anzahl um 1 erhoehen
            ## aus dem String eine float Zahl machen
            ind_coverage = float(line[3]) # individual coverage
            coverage += ind_coverage
            anzahl += 1

        ## am Schluss die Coverage/Anzahl dividieren um average coverage zu erhalten
            av_coverage = coverage/anzahl
        return av_coverage
        
    def calculate_gene_average_coverage(self):
        '''Diese Methode berechnet die Coverage fuer mein Gen
        :return average coverage fuer meinen Genbereich'''

        ## Sie soll zwischen meinem Genstart und -ende liegen, diese Infos sind in self.txStart und self.txEnd

        a = pybedtools.BedTool('HG00096.chrom11.ILLUMINA.bwa.GBR.low_coverage.20120522.bam')
        b = a.genome_coverage(bg=True)

        anzahl = 0
        coverage = 0
        av_coverage = 0

        for line in b:
            ## in line[1] steht der Anfang des Reads, in line[2] das Ende
            anfang = int(line[1])
            ende = int(line[2])

            ## wenn der Anfang spaeter oder gleich wie mein Anfang ist
            ## und das Ende frueher oder gleich wie mein Ende ist
            ## dann befinden wir uns innerhalb meines Gens
            if self.txStart <= anfang:
                if self.txEnd >= ende:
                    # der Rest ist wie bei der oberen Berechnung
                    ind_coverage = float(line[3]) # individual coverage
                    coverage += ind_coverage
                    anzahl += 1

            if anzahl > 0:
                av_coverage = coverage/anzahl

        return (av_coverage)

    def get_number_mapped_reads(self):
        ''' Diese Methode zaehlt die mapped reads.
        :return anzahl der mapped reads'''

        ## samfile wird wieder geoeffnet
        path_to_file = '/home/taka/medgen/assignment01/HG00096.chrom11.ILLUMINA.bwa.GBR.low_coverage.20120522.bam'
        samfile = pysam.AlignmentFile(path_to_file, "rb")
        anzahl = 0

        for read in samfile:
            ## da es kein read.is_mapped gibt, not unmapped
            if not read.is_unmapped:
                anzahl += 1

        return anzahl

    def get_gene_symbol(self):
        ''' Diese Methode holt nur das Gensymbol.
        :return Gensymbol'''
        return self.gene
        
    def get_region_of_gene(self):
        ''' Diese Methode holt das Chromosom, den Start und das Ende meines Gens.
        :return Chromosom, Start und End'''

        print("Chromosome: {}\nStart: {}\nEnd: {}".format(self.chrom, self.txStart, self.txEnd))
        
    def get_number_of_exons(self):
        '''Diese Methode gibt aus wieviele Exone in meinem Gen sind.
        :return anzahl der Exone'''

        return(self.exonCount)
    
    def print_summary(self):
        '''Diese Methode enthaelt die Formatierungen fuer alle Ergebnisse'''
        #damit die weiteren Methoden funktionieren, muss zuerst die fetch_gene_coordinates durchlaufen werden.
        ## das kann etwas dauern, bitte um Geduld.
        print("SAM Header:")
        self.get_sam_header()                                                                   # Version: 1.0, Sorting order of alignments: coordinate
        print("Properly paired reads: {}".format(self.get_properly_paired_reads_of_gene()))     # 908
        print("Reads with Indels: {}".format(self.get_gene_reads_with_indels()))                # 16

        ## Die Berechnung dauert leider ziemlich lange. Bitte um Geduld.
        print("Total Average Coverage: {}".format(self.calculate_total_average_coverage()))     # 5.608294198569065
        print("Gene Average Coverage: {}".format(self.calculate_gene_average_coverage()))       # 5.563932448733413

        print("Number of mapped reads: {}".format(self.get_number_mapped_reads()))              # 6396581
        print("Gene Symbol: {}".format(self.get_gene_symbol()))                                 # B3GNT3
        self.get_region_of_gene()                                                               # Chromosome: 19, Start: 17905918 End: 17924385
        print("Exon Count: {}".format(self.get_number_of_exons()))                              # 3

        
if __name__ == '__main__':
    print ("Assignment 1")
    print("Author:", __author__, "\n")
    assignment1 = Assignment1()
    assignment1.fetch_gene_coordinates("hg19", "ausgabe.txt")
    assignment1.print_summary()
