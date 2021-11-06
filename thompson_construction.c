#include <stdio.h>
#include <stdlib.h>
#include "thompson_construction.h"
// #include "set.h"
#include "nfa.h"
#include "string.h"
// #include "state_stack.h"

int state_id = 0;

// void eps_closure(State start_state, NFA *nfa, Set *closure_set) { /*TODO: int symbol*/
//     printf("\nstarting eps_closure...\n");
//     StateStack *stack = init_stack(nfa->states_no);     // at most capacity N where N is the number of states in the NFA
    
//     // store which states i already visited, so i dont push to stack duplicates
//     int alreadyVisited[nfa->states_no];
//     int i;
//     for (i=0; i<nfa->states_no; i++) {
//         alreadyVisited[i] = 0;
//     }

//     stack_push(stack, start_state);                                        // pushing to stack the start state
//     set_add_element(closure_set, start_state);
//     State state;
//     while(!stack_is_empty(stack)) {                                        // iterate through the stack while it's empty
//         state = stack_pop(stack);                                           // got my state. now let's see where we can go from here
//         printf("\nSTATE=%d, got %d edges from here\n", state.state_id, state.edges_no);
//         int edges_no = state.edges_no;
//         for (i=0; i<edges_no; i++) {                                        // iterate through states
//             Edge e = state.edges[i];
//             printf("\tedge: %d to %d, value=%d\n", e.src, e.dst, e.val);
//             if (e.val == 0) {  
//                 printf("\tthe link is epsilon, add to closure state %d\n", e.dst);                                             // if the link is epsilon
//                 State state_to_add = get_state_by_id(nfa, e.dst);
//                 set_add_element(closure_set, state_to_add);           // the element is in the closure, add it to set
//                 if (!alreadyVisited[e.dst]) {
//                     stack_push(stack, state_to_add);                              // add the state to the stack too, so we can check from there
//                 }
//             }
//         }
//         alreadyVisited[state.state_id] = 1;
//     }
//     printf("finished eps_closure.\n");

// }



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

NFA* nfa_build(char *reg_exp) {
    // il massimo numero di stati che puo avere e' 2k dove k e' il numero di simboli
    int i;
    char symbol;
    NFA *temp, *final;

    // iterate through the regular expression
    for (i=0; i<strlen(reg_exp); i++) {
        symbol = reg_exp[i];
        
        if (symbol == '|') {
            temp = nfa_union();    
        
        } else if (symbol == '.') {
            temp = nfa_concat();
        
        } else if (symbol == '*') {
            temp = nfa_closure();

        } else {
            temp = nfa_create(symbol);

        }    
    }
}

NFA* nfa_create(char symbol) {
    // create NFA
    NFA *_nfa = nfa();

    // ids for creating edge
    int initial_id = state_id++;
    int final_id = state_id++;

    _nfa->states[0] = initial_id;
    _nfa->states[1] = final_id;

    // create edge between states
    Edge *_edge = edge(initial_id, final_id, symbol);
    
    // put stuff together
    _nfa->transitions[0] = _edge;
    _nfa->initial_state = initial_id;
    _nfa->final_state = final_id;
}


NFA* nfa_concat() {

}

NFA* nfa_union() {

}

NFA* nfa_closure() {

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
        printf("%d ", i);
    }
    printf("\n");
    printf("Edges: \n");
    
    for (i=0; i<nfa->trans_no; i++) {
        Edge *e = nfa->transitions[i];
        printf("%d --%d--> %d\n", e->src, e->val, e->dst);
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

// /*  iterate through the nfa states; if find an initial state, 
//     add it to the set */
// void nfa_get_initial_state(NFA *nfa, Set *set) {
//     int i;
//     for (i=0; i<nfa->states_no; i++) {
//         if (nfa->states[i].state_type == 0) {
//             set_add_element(set, nfa->states[i]);
//         }
//     }
// }

// State get_state_by_id(NFA *nfa, int id) {
//     int i;
//     State state;        // may give problems if error
//     int found = 0;
//     for (i=0; i<nfa->states_no && !found; i++) {
//         if (nfa->states[i].state_id == id) {
//             found = 1;
//             state = nfa->states[i];
//         }
//     }
//     return state;
// }
