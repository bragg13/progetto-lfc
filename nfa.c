#include <stdio.h>
#include <stdlib.h>
#include "nfa.h"

NFA* nfa(int states_no, int edges_no) {
    NFA *n = malloc(sizeof(NFA));
    n->states_no = states_no;
    n->states = malloc(sizeof(int)*states_no);

    n->transitions = malloc(sizeof(Edge)*edges_no);
    n->trans_no = edges_no;

    return n;
}

Edge* edge(int initial_id, int final_id, char symbol) {
    Edge *e = malloc(sizeof(Edge));
    e->src = initial_id;
    e->dst = final_id;
    e->val = symbol;
    return e;
}

/* Print a NFA */
void nfa_print(NFA *nfa) {
    printf("\n");
    int i;
    int j;
    printf("====================\n");
    printf("Initial state: %d, Final state: %d\n", nfa->initial_state, nfa->final_state);
    
    printf("States: ");
    for (i=0; i<nfa->states_no; i++) {
        printf("%d ", nfa->states[i]);
    }
    printf("\n");
    printf("Edges: \n");
    
    for (i=0; i<nfa->trans_no; i++) {
        Edge *e = nfa->transitions[i];
        printf("%d --%c--> %d\n", e->src, e->val, e->dst);
    }

    printf("====================\n");

}

/* Free up memory by deallocating NFA */
int free_memory(NFA *nfa) {
    int i, j;
    
    free(nfa->states);                  // deallocate states
    
    // deallocate edge array
    for (i=0; i<nfa->trans_no; i++) {
        free(nfa->transitions[i]);
    }
    
    free(nfa);                          // deallocate nfa itself
    
    return 0;
}