#include <stdio.h>
#include <stdlib.h>
#include "subset_construction.h"
#include "set.h"
#include "nfa.h"

void eps_closure(State *start_state, NFA *nfa, Set *closure_set /*TODO: int symbol*/) {
    int edges_no = start_state->edges_no;           // how many transitions out of this state
    int i;                                          // iterator
    
    // foreach adjacent state
    for (i=0; i<edges_no; i++) {
        Edge e = start_state->edges[i];
        if (e.val == 0) {
            set_add_element(&closure_set, nfa->states[e.dst]);
        }
    }
}

void subset_construction(NFA *nfa, Set *alphabet) {

}
