#include <stdio.h>
#include <stdlib.h>
#include "nfa.h"

NFA* nfa() {
    NFA *n = malloc(sizeof(NFA));
    n->states_no = 2;
    n->trans_no = 2;
    n->states = malloc(sizeof(int)*2);
    n->transitions = malloc(sizeof(Edge));
    return n;
}

Edge* edge(int initial_id, int final_id, char symbol) {
    Edge *e = malloc(sizeof(Edge));
    e->src = initial_id;
    e->dst = final_id;
    e->val = symbol;
    return e;
}