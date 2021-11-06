#include <stdio.h>
#include <stdlib.h>
#include "int_stack.h"


/* Initializes a stack. */
IntStack* init_int_stack(unsigned int capacity) {
    IntStack *stack = (IntStack*) malloc(sizeof(IntStack));
    stack->capacity = capacity;
    stack->size = 0;
    stack->stack = (int*) malloc(sizeof(int)*capacity);
    return stack;
}

/* Couple of useful functions */ 
int int_stack_is_empty(IntStack *stack) { return (stack->size == 0) ? 1 : 0; }
int int_stack_is_full(IntStack *stack) { return (stack->size == stack->capacity) ? 1 : 0; }

/* Push function to add value to stack */
void int_stack_push(IntStack *stack, int num) {
    if (int_stack_is_full(stack)) {
        printf("size > capacity");
        return;
    }

    int i = stack->size;
    stack->stack[i] = num;
    stack->size++;
    // printf("pushed elemnt with id %d\n", num);
}


/* Push function to add value to stack */
int int_stack_pop(IntStack *stack) {
    if (int_stack_is_empty(stack)) {
        // printf("cant pop nothing");
        return -1;
    } 

    int i = stack->size-1;
    int num = stack->stack[i];
    stack->size--;
    return num;
}

/* Returns the element at the top without removing it */
int int_stack_peek(IntStack *stack) {
    if (int_stack_is_empty(stack)) {
        // printf("cant peek");
        return -1;
    } 

    int i = stack->size-1;
    int num = stack->stack[i];
    return num;
}


/* Prints a stack structure */
void print_int_stack(IntStack *stack, int is_char) {
    printf("IntStack: size=%d, capacity=%d\n", stack->size, stack->capacity);

    int size = stack->size;
    int i;

    if (is_char) {
        for (i=0; i<size; i++) {
            printf(" %c\n", (char) stack->stack[i]);
        }
    } else {
        for (i=0; i<size; i++) {
            printf(" %d\n", stack->stack[i]);
        }
    }
}
