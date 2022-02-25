# Algorithms

Solving common programming problems with algorithms.

## Fibonacci Algorithm

* Calculating the nth Fibonacci number using iterations vs. recursion.

Usage:  
`./fibonacci_numbers.py -n <number>`

## Towers of Hanoi

* Calculating the solution to the tower of hanoi problem.
* Returns instructions for moving the disks to solve the problem.

Usage:  
`./towers_of_hanoi.py -n <amount of disks>`

## Manhattan Tourist Problem

* First Iteration only using weights for down / right 

Usage:  
`./manhattan_tourist_problem.py mtp_weights`

* Additional weights for going the diagonal 

Usage:
`./manhattan_tourist_problem_diagonal.py mtp_diagonal_weights`

## Needleman Wunsch Algorithm

* Calculating the optimal global alignment of 2 DNA sequences (in fastA format)

Usage:
`./needleman-wunsch.py <optional: sequences.txt>`

* Calculating the optimal global alignment of 3 DNA sequences (in fastA format)

Usage:
`./needleman_wunsch_multiple_sequences.py <optional: 3_sequences.txt>`