#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>
#include "set.h"
#include "nfa.h"
#include "subset_construction.h"

typedef struct Stack {
    int capacity;
    int size;
    State **states;     // array of stateptr
} Stack;

/* basic functions */
void init_stack(Stack *stack, int capacity);
void print_stack(Stack *stack);

/* utils functions */
int isEmpty(Stack *stack);
int isEmpty(Stack *stack);

/* pop/push */
void push(Stack *stack, State *state);
State* pop(Stack *stack);

#endif