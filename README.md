# Progetto di LFC - Subset Construction

## `nfa.h` e `set.c`
Definizione ed implementazione di un NFA attraverso un grafo orientato.

#### `struct NFA`
Definito da un intero che indica il numero di stati presenti ed un array che conterrà gli stati.

#### `struct State`
Definito da due interi, indicanti il numero di transizioni uscenti e l'id dello stato, da un enumeratore che indica il tipo di stato (iniziale, standard o finale) e da un array di transizioni uscenti.

#### `struct Edge`
Definito da tre valori interi, che indicano lo stato sorgente, lo stato destinazione e il simbolo della transizione.

#### `void get_input(NFA *nfa)`
Funzione che apre un file "input.txt" dove dev'essere contenuta una rappresentazione numerica dell'NFA; il file viene analizzato e sulla sua base viene costruito l'automa.

#### `void print_nfa(NFA *nfa)`
Funzione che prende in input un NFA e ne stampa gli attributi.

#### `int free_memory(NFA *nfa)`
Funzione che dealloca un NFA per liberare la memoria.

<br>

## `set.h` e `set.c`
Definizione e implementazione di un Set attraverso un array.

####

## stack.h e stack.c

## subset_construction.h e subset_construction.c




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