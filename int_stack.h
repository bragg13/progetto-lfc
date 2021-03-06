#ifndef INT_STACK_H
#define INT_STACK_H

#include <stdio.h>
#include <stdlib.h>

typedef struct IntStack {
    unsigned int capacity;
    int size;
    int *stack;
} IntStack;

/* basic functions */
IntStack* init_int_stack(unsigned int capacity);
void print_int_stack(IntStack *stack, int is_char);
void int_stack_push(IntStack *stack, int num);
int int_stack_pop(IntStack *stack);
int int_stack_peek(IntStack *stack);

/* useful functions */
int int_stack_is_full(IntStack *stack);
int int_stack_is_empty(IntStack *stack);

#endif