#! /usr/bin/env python2

import vcf
from vcf import utils
import hgvs
import hgvs.dataproviders.uta
import hgvs.parser
import hgvs.assemblymapper
from bioutils.assemblies import make_name_ac_map

__author__ = 'Anna Majewski'


## Damit das Programm funktioniert, musste der Interpreter auf 2.7. gestellt werden.


class Assignment3:
    def __init__(self):
        ## Check if pyvcf is installed
        print("PyVCF version: %s" % vcf.VERSION)
        ## Check if hgvs is installed
        print("HGVS version: %s" % hgvs.__version__)

        ## Dateinamen in Variablen fuer Vater und Mutter
        self.filename_mother = 'AmpliseqExome.20141120.NA24143.vcf'
        self.filename_father = 'AmpliseqExome.20141120.NA24149.vcf'
        self.filename_son = 'AmpliseqExome.20141120.NA24385.vcf'

        ## Oeffnen mit vcf.Reader
        self.file_mother = vcf.Reader(open(self.filename_mother, 'r'))
        self.file_father = vcf.Reader(open(self.filename_father, 'r'))
        self.file_son = vcf.Reader(open(self.filename_son, 'r'))

    def get_total_number_of_variants_mother(self):
        '''
        Return the total number of identified variants in the mother
        :return: total number of identified variants in the mother
        '''
        ## Oeffnen mit vcf.Reader
        self.file_mother = vcf.Reader(open(self.filename_mother, 'r'))
        anzahl = 0
        for record in self.file_mother:
            anzahl += 1
        return anzahl

    def get_total_number_of_variants_father(self):
        '''
        Return the total number of identified variants in the father
        :return: total number of identified variants in the father
        '''
        ## Oeffnen mit vcf.Reader
        self.file_father = vcf.Reader(open(self.filename_father, 'r'))
        anzahl = 0
        for record in self.file_father:
            anzahl += 1
        return anzahl

    def get_variants_shared_by_father_and_son(self):
        '''
        Return the number of identified variants shared by mother and son
        Also returns a file containing the variants.
        :return:
        '''
        ## Oeffnen mit vcf.Reader
        self.file_father = vcf.Reader(open(self.filename_father, 'r'))
        self.file_son = vcf.Reader(open(self.filename_son, 'r'))

        anzahl = 0

        ## geteilt verwendet utils.walk_together um ueber mehrere Dateien zu iterieren
        geteilt = utils.walk_together(self.file_father, self.file_son)
        father_son = open("father_son.vcf", "w")

        for record in geteilt:
            ## record[0] entspricht dem Vater, record[1] entspricht dem Sohn
            ## wenn diese records nicht leer sind, dann wird die Anzahl um 1 erhoeht.
            if not record[0] is None and not record[1] is None:
                anzahl += 1
                ## Durch einen Hinweis von Frank Ruge habe erst verstanden, dass hier nicht nur die Anzahl der Variants,
                ## sondern auch die Variants an sich gefragt sind. Deshalb wurden sie auf diese Weise angefuegt.
                for eintrag in record:
                    writer = vcf.Writer(father_son, self.file_son, "\n")
                    writer.write_record(eintrag)

        return anzahl

    def get_variants_shared_by_mother_and_son(self):
        '''
        Return the number of identified variants shared by mother and son
        Also returns a file containing the variants.
        :return: 
        '''
        ## Oeffnen mit vcf.Reader
        self.file_mother = vcf.Reader(open(self.filename_mother, 'r'))
        self.file_son = vcf.Reader(open(self.filename_son, 'r'))

        anzahl = 0

        geteilt = utils.walk_together(self.file_mother, self.file_son)
        mother_son = open("mother_son.vcf", "w")
        for record in geteilt:
            ## record[0] entspricht der Mutter, record[1] entspricht dem Sohn
            ## wenn diese records nicht leer sind, dann wird die Anzahl um 1 erhoeht.
            if not record[0] is None and not record[1] is None:
                anzahl += 1
                for eintrag in record:
                    writer = vcf.Writer(mother_son, self.file_son, "\n")
                    writer.write_record(eintrag)

        return anzahl

    def get_variants_shared_by_trio(self):
        '''
        Return the number of identified variants shared by father, mother and son
        Also returns a file containing the variants.
        :return:
        '''
        ## Oeffnen mit vcf.Reader
        self.file_mother = vcf.Reader(open(self.filename_mother, 'r'))
        self.file_father = vcf.Reader(open(self.filename_father, 'r'))
        self.file_son = vcf.Reader(open(self.filename_son, 'r'))

        anzahl = 0

        geteilt = utils.walk_together(self.file_mother, self.file_father, self.file_son)
        mother_father_son = open("mother_father_son.vcf", "w")
        for record in geteilt:
            ## record[0] entspricht der Mutter, record[1] entspricht dem Vater und record[2] entspricht dem Sohn
            ## wenn diese records nicht leer sind, dann wird die Anzahl um 1 erhoeht.
            if not record[0] is None and not record[1] is None and not record[2] is None:
                anzahl += 1
                for eintrag in record:
                    writer = vcf.Writer(mother_father_son, self.file_son, "\n")
                    writer.write_record(eintrag)

        return anzahl

    def merge_mother_father_son_into_one_vcf(self):
        '''
        Creates one VCF containing all variants of the trio (merge VCFs)
        :return: 
        '''
        ## class vcf.Writer(stream, template, lineterminator='n')[source]
        ## der Writer benoetigt ein template, aus dem die metadaten uebernommen werden
        ## ich habe mich fuer den Sohn entschieden
        ## ein Stream im Modus write wird geoeffnet
        trio_file = open("trio_file.vcf", "w")
        writer = vcf.Writer(trio_file, self.file_son, "\n")
        ## http://nullege.com/codes/search/vcf.utils.walk_together
        ## um mehrere vcf Files gleichzeitig zu bearbeiten kann man vcf.utils.walk_together benutzen
        for records in utils.walk_together(self.file_father, self.file_father, self.file_son):
            ## jeder Eintrag der nicht None ist wird in das VCF geschrieben
            for eintrag in records:
                if eintrag is not None:
                    writer.write_record(eintrag)

        success = "The file has been merged successfully to trio_file.vcf"

        return success

    def convert_first_variants_of_son_into_HGVS(self):
        '''
        Convert the first 100 variants identified in the son into the corresponding transcript HGVS.
        Each variant should be mapped to all corresponding transcripts. Pointer:
        - https://hgvs.readthedocs.io/en/master/examples/manuscript-example.html#project-genomic-variant-to-a-new-transcript
        :return: mapping of variant to corresponding transcripts
        '''
        ## von SPabinger so uebernommen:
        ## Connect to UTA
        hdp = hgvs.dataproviders.uta.connect()

        ## Used to get the transcripts
        # normalize = False wird genommen um die Warnung zu unterdruecken
        assembly_mapper = hgvs.assemblymapper.AssemblyMapper(hdp, normalize=False)  # EasyVariantMapper before

        ## Used for parsing
        hgvsparser = hgvs.parser.Parser()  # Parser

        ## Oeffnen des Streams fuer den Sohn:
        self.file_son = vcf.Reader(open(self.filename_son, 'r'))

        anzahl = 0
        success = 0
        exception = 0

        print("Starting conversion. Please wait.")

        for record in self.file_son:
            ## Oeffnen einer Datei, damit das Ergebnis in einer Datei steht.
            ## Mode = a fuer append, damit die Zeilen angefuegt und nicht ueberschrieben werden
            file = open('100variants.hgvs', 'a')
            if anzahl < 100:
                ## Get chromosome mapping
                refseq_nc_number = make_name_ac_map("GRCh37.p13")[record.CHROM[3:]]
                ## Format: nc_number :g. position reference > alternative
                genome_hgvs = "%s:g.%s%s>%s" % (refseq_nc_number, str(record.POS), str(record.REF), str(record.ALT[0]))
                try:
                    genom = hgvsparser.parse_hgvs_variant(genome_hgvs)
                    for transcript in assembly_mapper.relevant_transcripts(genom):
                        try:
                            ## ist es eine codierende Sequenz?
                            coding = assembly_mapper.g_to_c(genom, transcript)
                            success += 1
                            file.write("Number of variant: %s\n%s corresponds to the coding sequence %s\n" % (anzahl+1, genom, coding))
                        except hgvs.exceptions.HGVSUsageError:
                            ## ist es keine codierende Sequenz?
                            noncoding = assembly_mapper.g_to_n(genom, transcript)
                            success += 1
                            file.write("Number of variant: %s\n%s corresponds to the noncoding sequence %s\n" % (anzahl + 1, genom, noncoding))
                        except:
                            ## ansonsten ist es eine exception
                            exception += 1
                except Exception:
                    exception += 1

            else:
                ## sobald die ersten 100 Varianten durch sind, abbrechen
                break
            ## jede Runde wird die Anzahl um 1 erhoeht.
            anzahl += 1
            ## eine kleine Hilfe, die anzeigt wie weit wir schon sind.
            if anzahl == 10:
                print("Conversion is at 10%")
            if anzahl == 25:
                print("Conversion is at 25%")
            if anzahl == 50:
                print("Conversion is at 50%")
            if anzahl == 75:
                print("Conversion is at 75%")
            if anzahl == 90:
                print("Conversion is at 90%")

        print ("Number of successfull mappings: {}\n"
               "Number of exceptions: {}".format(success, exception))

    def print_summary(self):
        ## Hier werden alle Methoden aufgerufen und mit einem String versehen, der beschreibt was sie ausgeben.
        print("Total Number of Variants in the Mother: %s" % self.get_total_number_of_variants_mother())                # 38693
        print("Total Number of Variants in the Father: %s" % self.get_total_number_of_variants_father())                # 38641
        print("Total Number of Variants shared by Father and Son: %s" % self.get_variants_shared_by_father_and_son())   # 30142
        print("Total Number of Variants shared by Mother and Son: %s" % self.get_variants_shared_by_mother_and_son())   # 30216
        print("Total Number of Variants shared by all three: %s" % self.get_variants_shared_by_trio())                  # 22533
        print("Merge status: %s" % self.merge_mother_father_son_into_one_vcf())
        ## Hier werden alle passenden Mappings zu den Varianten gesucht. Das dauert eine Weile.
        ## Bei 10, 25, 50, 75 und 90% wird ausgegeben, dass man schon so weit ist.
        ## Die Varianten werden in eine Datei geschrieben: 100variants.hgvs
        ## Bitte um Geduld.
        print("_____________")
        self.convert_first_variants_of_son_into_HGVS()

if __name__ == '__main__':
    print("Assignment 3")
    print("Author: %s\n" % __author__)
    assignment3 = Assignment3()
    assignment3.print_summary()
