#ifndef STATE_STACK_H
#define STATE_STACK_H

#include <stdio.h>
#include <stdlib.h>
#include "set.h"
#include "nfa.h"

typedef struct StateStack {
    unsigned int capacity;
    int size;
    State *states;
} StateStack;

/* basic functions */
StateStack* init_stack(unsigned int capacity);
void print_stack(StateStack *stack);

/* utils functions */
int stack_is_full(StateStack *stack);
int stack_is_empty(StateStack *stack);

/* pop/push */
void stack_push(StateStack *stack, State state);
State stack_pop(StateStack *stack);

#endif