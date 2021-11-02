#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>
#include "set.h"
#include "nfa.h"

typedef struct Stack {
    unsigned int capacity;
    int size;
    State *states; 
} Stack;

/* basic functions */
Stack* init_stack(unsigned int capacity);
void print_stack(Stack *stack);

/* utils functions */
int stack_is_full(Stack *stack);
int stack_is_empty(Stack *stack);

/* pop/push */
void stack_push(Stack *stack, State state);
State stack_pop(Stack *stack);

#endif