# Introduction to Linux and Shell Scripting

## AWK script
* Parse a .gff3 file (common format in bioinformatics) to filter out all genes 

Usage: `./parse_genes.sh cbs7435.gff3`

## Interactive AWK script
* Use the same input file and parse different features

Usage: `./parse_feature.sh cbs7435.gff3`

Possible features: 
* gene
* chromosome
* CDS
* mRNA
* exon
* five_prime_UTR
* three_prime_UTR