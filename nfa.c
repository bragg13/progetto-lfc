#include "nfa.h"

/* Initializes an NFA structure */
NFA* nfa(int states_no, int edges_no) {
    NFA *n = malloc(sizeof(NFA));
    n->states_no = states_no;
    n->states = malloc(sizeof(int)*states_no);

    n->transitions = malloc(sizeof(Edge)*edges_no);
    n->trans_no = edges_no;

    return n;
}

/* Initializes an Edge structure */
Edge* edge(int initial_id, int final_id, char symbol) {
    Edge *e = malloc(sizeof(Edge));
    e->src = initial_id;
    e->dst = final_id;
    e->val = symbol;
    return e;
}

/* Prints a NFA structure */
void nfa_print(NFA *nfa) {
    printf("\n");
    int i;
    int j;
    printf("========== NFA ==========\n");
    printf("| Initial state: %d, Final state: %d\n", nfa->initial_state, nfa->final_state);
    
    printf("| States: ");
    for (i=0; i<nfa->states_no; i++) {
        printf("%d ", nfa->states[i]);
    }
    printf("\n");
    printf("| Edges: \n");
    
    for (i=0; i<nfa->trans_no; i++) {
        Edge *e = nfa->transitions[i];
        printf("| %d --%c--> %d\n", e->src, e->val, e->dst);
    }

    printf("=========================\n");

}

/* Frees up memory by deallocating NFA */
void nfa_free(NFA *nfa) {
    free(nfa->states);                      // deallocate states array

    int i;
    for(i=0; i<nfa->trans_no; i++) {        // deallocate transitions array
        free(nfa->transitions[i]);
    }
    free(nfa->transitions);

    free(nfa);                              // deallocate nfa itself
}
