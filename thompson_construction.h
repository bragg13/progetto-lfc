#ifndef THOMPSON_CONSTRUCTION_H
#define THOMPSON_CONSTRUCTION_H

#include <stdio.h>
#include <stdlib.h>
#include "nfa.h"


/* input management */
char* get_input();

NFA* nfa_build(char *reg_exp);
NFA* nfa_create(char symbol);

NFA* nfa_concat(NFA* nfa1, NFA* nfa2);
NFA* nfa_union(NFA* nfa1, NFA* nfa2);
NFA* nfa_kleene(NFA* nfa1);

/* function prototypes */
void nfa_print(NFA *nfa);


#endif // end THOMPSON_CONSTRUCTION_H
