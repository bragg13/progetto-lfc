#ifndef NFA_STACK_H
#define NFA_STACK_H

#include <stdio.h>
#include <stdlib.h>
#include "nfa.h"

typedef struct NfaStack {
    unsigned int capacity;
    int size;
    NFA **stack;
} NfaStack;

/* basic functions */
NfaStack* init_nfa_stack(unsigned int capacity);
void print_nfa_stack(NfaStack *stack);

/* utils functions */
int nfa_stack_is_full(NfaStack *stack);
int nfa_stack_is_empty(NfaStack *stack);

/* pop/push */
void nfa_stack_push(NfaStack *stack, NFA *nfa);
NFA* nfa_stack_pop(NfaStack *stack);
NFA* nfa_stack_peek(NfaStack *stack);

#endif