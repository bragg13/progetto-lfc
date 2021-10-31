#ifndef SUBSET_CONSTRUCTION_H
#define SUBSET_CONSTRUCTION_H

#include <stdio.h>
#include <stdlib.h>

void eps_closure(State *start_state, NFA *nfa, Set *closure_set /*TODO: int symbol*/);

void subset_construction();

#endif // end SUBSET_CONSTRUCTION_H
