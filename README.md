# Progetto di LFC - Thompson Construction


> Il report accompagnatorio deve essere un pdf in cui si specificano:
> - come fornire l'input (obbligatorio)
> - come leggere l'output (obbligatorio)
> - che tipo di strutture dati sono state utilizzate per memorizzare grammatiche e/o automi e/o tabelle e/o altri elementi rilevanti al caso (facoltativo)
> - che tipo di test sono stati fatti (facoltativo)


## Introduction
C implementation of algorithm to parse a regular expression and generate from it a non-deterministic finite(?) automaton, i.e. Thompson Construction.

The original Thompson definition is recursive, and defines an NFA as made of (?) two states, one initial and one final, connected through a transition which may have an epsilon value or a value from the recognized alphabet.

Then we can perform three different operation on NFAs: 
- union, represented by the symbol |
- concatenation, represented by the symbol . (which can be implicit)(?)
- kleene start, represented by the symbol *

There are also two parenthesis symbols, ( and ), used to explicitly specify priority order.

The algorithm first checks if the given expression has implicit concatenation symbols to add, then converts it into a more convenient postfix format.

At this point, it iterates through the given expression and
- if there's an operatio symbol, pushes it
- creates an NFA outherwise

...


## Input
The input must be given as a .txt file. By default, the program will look for a file called "input.txt": this can be overidden(?) by using the option "-i" and specifying a different file.

The input file contains two lines: 
- first one: integer - represents the number of characters in the following line
- second one: string - represents a regular expression

Allowed characters in input are:
- letters a-z
- letters A-Z
- digits  0-9
- operation symbols | . + ( )


## Output
The output is given as a .txt file. By default, the name of this file will be "output.txt": this can be overidden(?) by using the option "-o" and specifying a different file.

The output file contains a variable number of lines and can be given in two different styles, default or human-readable:

- ### Default

- ### Human-readable
    - the first and last line are just decoration lines
    - the second line contains the ID of the initial NFA state
    - the third line contains the ID of the final NFA state
    - the fourth line contains the list of states i.e. a list of integers each one being a state ID
    - from sixth line forward(?) are listed transitions, unordered, and the pattern is `<source state id> -- <transition value> --> <destiation state id>`


## Constrains

## Implementation - Data Structures

## Implementation - Tests performed

## Notes about the code

## Console help
```
Usage: 
    -i <path> specify a file to use as input file
    -o <path> specify a file to use as output file
    -hr use human-readable output
    -h display this message"
```


The implementation is based on original Ken Thompson's
The algorithm aims to transform a regular expression into an equivalent NFA (non deterministic finite automaton)
It works recursively taking as input a regular expression casted to postfix notation through the *** algorithm.
It parses the regular expression into its constituient subespressions, then applies operators to connect them into a bigger one.

BASIS:
The automaton of the word "a" can be defined as:
    2 1     # 2 states, 1 transition
    i 0 1   # state name: i, initial, 1 transition out
    f 2 0   
    i f 0   # trans type: eps, from i to f

INDUCTION:
Having t

Rules:
    - the number of transitions leaving any state is max 2
    

[from Wikipedia, https://en.wikipedia.org/wiki/Thompson%27s_construction]

support only literals and one-digit numbers as alphabet

removing input length from input was an option but turned out to be more expensive than useful


TODO: epsilon needs to be different from e orelse I cant use e even tho is in the alphabet
TODO: output non-hr
TODO: maybe I could order the output?