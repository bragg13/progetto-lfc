#ifndef NFA_H
#define NFA_H

#include <stdio.h>
#include <stdlib.h>
#include "int_stack.h"

/* define structures */
typedef struct NFA {
    int states_no;                      // number of states
    int trans_no;                       // number of transitions

    struct Edge **transitions;          // array of transitions
    int *states;                        // array of states

    int initial_state, final_state;     // initial/final state id
} NFA;

typedef struct Edge {
    int src;                            // edge source
    int dst;                            // edge destination
    char val;                           // edge value
} Edge;

/* Constructors */
NFA *nfa();
Edge *edge(int initial_id, int final_id, char symbol);

/* Other functions */
void nfa_print(NFA *nfa);
void nfa_free(NFA *nfa);

/* Topsort implementation for ordered output */
void topsort(NFA *nfa, IntStack *s);
void topsort_rec(NFA *nfa, IntStack *s, int *visited, int i);

#endif
