# Medical Genome Analysis

## Assignment 01
Get information about an assigned gene using a [BAM file](ftp://ftp.1000genomes.ebi.ac.uk/vol1/ftp/phase3/data/HG00096/alignment/HG00096.chrom11.ILLUMINA.bwa.GBR.low_coverage.20120522.bam). 

* Fetch gene coordinates
* Get SAM header
* Calculate properly paired reads of gene
* Find inDels in gene
* Calculate total average coverage
* Calculate gene average coverage
* Calculate mapped reads
* Get basic information of the gene 

## Assignment 02
Perform gene analysis based on a human genome ([HG002-NA24385-huAA53E0](ftp://ftp-trace.ncbi.nlm.nih.gov/giab/ftp/data/AshkenazimTrio/analysis/IonTorrent_TVC_03162015/AmpliseqExome.20141120.NA24385.vcf)) of a person. 

* Calculate the average quality of all gene variants
* Get the number of variants
* Calculate number of InDels
* Calculate number of SNVs (small nuclear variants)
* Calculate number of heterozygous variants 

## Assignemtn 03
Comparative analysis of the genome of a family: mother ([HG004-NA24143-hu8E87A9](ftp://ftp-trace.ncbi.nlm.nih.gov/giab/ftp/data/AshkenazimTrio/analysis/IonTorrent_TVC_03162015/AmpliseqExome.20141120.NA24143.vcf)), father ([HG003-NA24149-hu6E4515](ftp://ftp-trace.ncbi.nlm.nih.gov/giab/ftp/data/AshkenazimTrio/analysis/IonTorrent_TVC_03162015/AmpliseqExome.20141120.NA24149.vcf)) and son ([HG002-NA24385-huAA53E0](ftp://ftp-trace.ncbi.nlm.nih.gov/giab/ftp/data/AshkenazimTrio/analysis/IonTorrent_TVC_03162015/AmpliseqExome.20141120.NA24385.vcf)))

* Get variants for mother, father and son
* Compare variants shared by father and son / mother and son / the whole family
* Convert results in HGVS (Human Genome Variation Society) format

All genomes are openly available for research via NCBI. 
