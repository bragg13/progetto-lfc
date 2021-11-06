#ifndef NFA_H
#define NFA_H

#include <stdio.h>
#include <stdlib.h>

/* define structures */
typedef struct NFA {
    int states_no;
    int trans_no;

    struct Edge **transitions;
    int *states;

    int initial_state, final_state;
} NFA;

typedef struct Edge {
    int src;
    int dst;
    char val;
} Edge;

NFA *nfa();
Edge *edge(int initial_id, int final_id, char symbol);

void nfa_print(NFA *nfa);

int free_memory(NFA *nfa);

#endif // NFA_H
