#include <stdio.h>
#include <stdlib.h>
#include "thompson_construction.h"
#include "set.h"
#include "nfa.h"
#include "state_stack.h"


void eps_closure(State start_state, NFA *nfa, Set *closure_set) { /*TODO: int symbol*/
    printf("\nstarting eps_closure...\n");
    StateStack *stack = init_stack(nfa->states_no);     // at most capacity N where N is the number of states in the NFA
    
    // store which states i already visited, so i dont push to stack duplicates
    int alreadyVisited[nfa->states_no];
    int i;
    for (i=0; i<nfa->states_no; i++) {
        alreadyVisited[i] = 0;
    }

    stack_push(stack, start_state);                                        // pushing to stack the start state
    set_add_element(closure_set, start_state);
    State state;
    while(!stack_is_empty(stack)) {                                        // iterate through the stack while it's empty
        state = stack_pop(stack);                                           // got my state. now let's see where we can go from here
        printf("\nSTATE=%d, got %d edges from here\n", state.state_id, state.edges_no);
        int edges_no = state.edges_no;
        for (i=0; i<edges_no; i++) {                                        // iterate through states
            Edge e = state.edges[i];
            printf("\tedge: %d to %d, value=%d\n", e.src, e.dst, e.val);
            if (e.val == 0) {  
                printf("\tthe link is epsilon, add to closure state %d\n", e.dst);                                             // if the link is epsilon
                State state_to_add = get_state_by_id(nfa, e.dst);
                set_add_element(closure_set, state_to_add);           // the element is in the closure, add it to set
                if (!alreadyVisited[e.dst]) {
                    stack_push(stack, state_to_add);                              // add the state to the stack too, so we can check from there
                }
            }
        }
        alreadyVisited[state.state_id] = 1;
    }
    printf("finished eps_closure.\n");

}

void subset_construction(NFA *nfa, Set *alphabet) {

}


char* get_input() {
    FILE *fp;
    int length;

    fp = fopen("input.txt", "r");
    if (fp == NULL) {
        perror("Failed opening file");
        return NULL;
    }

    fscanf(fp, "%d", &length);

    if (length <= 0) {
        perror("Length cant be 0 or less");
        return NULL;
    }

    char *str = malloc(sizeof(char)*length+1);      // DEALLOC
    fscanf(fp, "%s", str);
    fclose(fp);

    str[length] = '\0';
    return str;
}


/* Print a NFA */
void print_nfa(NFA *nfa) {
    printf("\n");
    int i;
    int j;
    for (i=0; i<nfa->states_no; i++) {
        printf("State: %d", i);
        switch (nfa->states[i].state_type) {
        case 0:
            printf(" - initial\n");
            break;
        case 1:
            printf(" - default\n");
            break;
        case 2:
            printf(" - final\n");
            break;
        }

        for (j=0; j<nfa->states[i].edges_no; j++) {
            Edge e = nfa->states[i].edges[j];
            printf("\t- %d to %d [%d]\n", e.src, e.dst, e.val);
        }
        
        printf("\n");
    }
}

/* Free up memory by deallocating NFA */
int free_memory(NFA *nfa) {
    int i, j;
    
    // deallocate edge array
    for (i=0; i<nfa->states_no; i++) {
        free(nfa->states[i].edges);
    }
    free(nfa->states);                  // deallocate states
    free(nfa);                          // deallocate nfa itself
    
    return 0;
}

/*  iterate through the nfa states; if find an initial state, 
    add it to the set */
void nfa_get_initial_state(NFA *nfa, Set *set) {
    int i;
    for (i=0; i<nfa->states_no; i++) {
        if (nfa->states[i].state_type == 0) {
            set_add_element(set, nfa->states[i]);
        }
    }
}

State get_state_by_id(NFA *nfa, int id) {
    int i;
    State state;        // may give problems if error
    int found = 0;
    for (i=0; i<nfa->states_no && !found; i++) {
        if (nfa->states[i].state_id == id) {
            found = 1;
            state = nfa->states[i];
        }
    }
    return state;
}
