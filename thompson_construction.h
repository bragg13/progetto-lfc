#ifndef THOMPSON_CONSTRUCTION_H
#define THOMPSON_CONSTRUCTION_H

#include <stdio.h>
#include <stdlib.h>
#include "nfa.h"
#include "string.h"
#include "int_stack.h"
#include "nfa_stack.h"

/* I/O management */
char* get_input(char *input_str);
void write_output(NFA *nfa, char *output_str, int output_type);

/* NFA basics */
NFA* nfa_build(char *reg_exp);
NFA* nfa_create(char symbol);
void nfa_print(NFA *nfa);

/* operations */
NFA* nfa_concat(NFA* nfa1, NFA* nfa2);
NFA* nfa_union(NFA* nfa1, NFA* nfa2);
NFA* nfa_kleene(NFA* nfa1);

#endif
