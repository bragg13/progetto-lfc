#ifndef THOMPSON_CONSTRUCTION_H
#define THOMPSON_CONSTRUCTION_H

#include <stdio.h>
#include <stdlib.h>
#include "nfa.h"
#include "set.h"

void eps_closure(State start_state, NFA *nfa, Set *closure_set /*TODO: int symbol*/);

/* input management */
char* get_input();

// void translateInput();


/* function prototypes */
void print_nfa(NFA *nfa);

int free_memory(NFA *nfa);

void nfa_get_initial_state(NFA *nfa, Set *set);

State get_state_by_id(NFA *nfa, int id);

#endif // end THOMPSON_CONSTRUCTION_H
