# LFC - Thompson Construction

> Il report accompagnatorio deve essere un pdf in cui si specificano:
> - come fornire l'input (obbligatorio)
> - come leggere l'output (obbligatorio)
> - che tipo di strutture dati sono state utilizzate per memorizzare grammatiche e/o automi e/o tabelle e/o altri elementi rilevanti al caso (facoltativo)
> - che tipo di test sono stati fatti (facoltativo)


## Introduction
The following project is a C implementation of algorithm to parse a regular expression and generate from it a non-deterministic automaton, i.e. Thompson Construction.

The original Thompson definition is recursive, and defines an NFA as a structure made of two states, an initial one and a final one, connected through a transition which may have an epsilon value (for whom I decided to use the '#' symbol) or a value from the recognized alphabet.

Then we can perform three different operation on NFAs: 
- **union**, represented by the symbol |
- **concatenation**, represented by the symbol . (which can be implicit)
- **kleene start**, represented by the symbol *

There are also two parenthesis symbols, ( and ), used to explicitly specify priority order.

The algorithm is split up in three steps:

1. we first check if the given expression has **implicit concatenation**: if that is the case, we explicit it;

2. then, we **convert** the resulting expression into a more convenient **postfix format**;

3. at this point, the actual algorithm begins and iterates through the expression:
    - if the symbol represents an **operation**, then we pop the first two elements (or only the first one, in the case of kleene star), **apply the specified operation**, and finally push the resulting NFA to stack 
    - otherwise, we **create an NFA** with the transition having the specified symbol as value 

<br>

## Input
The input must be given as a .txt file. 
By default, the program will look for a file called "input.txt": this can be overidden by using the option "-i" and specifying a different file.

The input file must contain two lines: 
- first one: *integer* - represents the number of characters in the following line [1]
- second one: *string* - represents a regular expression

Allowed characters in input are:
- letters a-z
- letters A-Z
- digits  0-9
- operation symbols | . + ( ) 
- epsilon symbol #

<br>

## Output
The output is given as a .txt file. 
By default, the name of this file will be "output.txt": this can be overidden by using the option "-o" and specifying a different file.

The output file contains a variable number of lines and can be given in two different styles, default or human-readable:

- ### Default
    - the first line contains two integers representing the initial and the final state IDs
    - the second line contains the list of states i.e. a list of integers, each one being a state ID
    - from sixth line forward are listed transitions, unordered [2]; each line has three integers, representing the source state, the destination state and the transition value

- ### Human-readable
    - the first and last line are just decoration lines
    - the second line contains the ID of the initial NFA state
    - the third line contains the ID of the final NFA state
    - the fourth line contains the list of states i.e. a list of integers each one being a state ID
    - from sixth line forward are listed transitions, unordered, and the pattern is `<source state id> -- <transition value> --> <destiation state id>`

<br>

## Implementation - Data Structures
- ### Stack (node/int)
    The stack implementation is basically the same for the integer one and the NFA one, the differences are only related to data types.

    The structure is made of an array (of integers or pointers to NFA) where elements get stored, one integer for capacity and one for current size (and thus also the index of the head element).

    Since I don't know the capacity a priori, there's a method to dynamically initialize the stack using malloc; hence, there is also a method to free up the memory. 
    The other functions are normal stack methods, and are briefly described with comments. 

- ### NFA
    NFA is defined as a structure resembling a graph. 
    There are two integers to store the number of states and transitions; there is an array of integers, to store states, and an array of pointers to Edge, to store transitions; there are two integers to store the id of initial and final states.

    It contains a method to initialize an NFA dynamically and two methods for printing and memory freeing.

- ### Edge
    Edge is a structure representing a transition. It just contains two integers to store the soource and destination states, and a char to store the value of the transition.


- ### Regular Expression
    Regular expressions are not represented through a struct, since they basically are strings. However, there are three functions to deal with them.
    - `get_priotity`, used to retrieve the priority of a given operator
    - `add_explicit_concat`, used to add an explicit concat symbol
    - `infix_to_postfix`, used to convert the expression to postfix notation


## Implementation - Tests performed
I tested the whole program with a bunch of regular expressions and manually checked whether the result was correct or not.
The following are the tested expressions along with the input file name, located in the `test` folder:

- `abc`, input1.txt
- `(0|1)*1`, input2.txt
- `(#|a*b)`, input3.txt
- `(a|b)*abb`, input4.txt
- `b*(a|b|#)*`, input5.txt


## Notes about the code
- The states could be not sequential because of the concatenation operation, which merges two states into a new merged one.

- Variables in regular expressions are one-letter only.

- [1] Specifying the number of characters in the next line could have been omitted and replaced with a modification of the get_input function; however, it would have been trickier to read the input expression because of memory allocation for the string: I don't think the improvement would be worth.

- [2] Ordering the output could have been implemented, but I found it to be not worth it too.

<br>

## Console help
```
Usage: 
    -i <path> specify a file to use as input file
    -o <path> specify a file to use as output file
    -H use human-readable output
    -h display this message"

Example:
    ./app.out - Launch app with file input.txt 
    ./app.out -H -i test/input1.txt - Launch app with file test/input1.txt and writing output in human readable mode
    ./app.out -o test/output.txt - Launch app with file input.txt and writing output in default mode in file test/output.txt
```

<br>

## Credits
Andrea Bragante - andrea.bragante@studenti.unitn.it