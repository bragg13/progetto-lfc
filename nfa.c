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

/* Topological sort algorithm */
void topsort(NFA *nfa, IntStack *s) {
    int max_number = nfa->final_state+1;    // final state is the highest possible state id (itself, that's why the +1) in the nfa
    int visited[max_number];

    // set visited to false
    int i;
    for (i=0; i<=max_number; i++) {
        visited[i] = 0;
    }

    // iterate through states; if not visited yet, visit it
    int state;
    for (i=0; i<nfa->states_no; i++) {
        state = nfa->states[i];
        if (visited[state] == 0) {
            topsort_rec(nfa, s, visited, state);
        }
    }
}

/* Recursive part for topological sort */
void topsort_rec(NFA *nfa, IntStack *s, int *visited, int i) {
    // visit the node
    visited[i] = 1;

    // iterare through all transitions looking for adjacents to i
    int j, dest;
    for (j=0; j<nfa->trans_no; j++) {

        // if a node is adjacent to i and it's not visited yet, visit it
        if (nfa->transitions[j]->src == i) {
            dest = nfa->transitions[j]->dst;

            if (visited[dest] == 0) {
                topsort_rec(nfa, s, visited, dest);
            }
        }
    }

    // push node to stack
    int_stack_push(s, i);
}