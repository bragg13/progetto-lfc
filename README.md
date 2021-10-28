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