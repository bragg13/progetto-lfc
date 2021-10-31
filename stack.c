#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

/* Initializes a stack. */
void init_stack(Stack *stack, int capacity) {
    stack->capacity = capacity;
    stack->size = 0;
    stack->states = malloc(sizeof(State*)*capacity);
}

/* Couple of useful functions */ 
int isEmpty(Stack *stack) { return (stack->size == 0) ? 1 : 0; }
int isFull(Stack *stack) { return (stack->size == stack->capacity) ? 1 : 0; }

/* Push function to add value to stack */
void push(Stack *stack, State *state) {
    if (isFull(stack)) {
        printf("size > capacity");
        return;
    }

    int i = stack->size;
    stack->states[i] = state;
    stack->size++;
}


/* Push function to add value to stack */
State* pop(Stack *stack) {
    if (isEmpty(stack)) {
        printf("cant pop nothing");
    } else {
        int i = stack->size;
        State *s = stack->states[i];
        stack->size--;
        return s;
    }

}

/* Prints a stack structure */
void print_stack(Stack *stack) {
    printf("Stack: size=%d, capacity=%d\n", stack->size, stack->capacity);

    int size = stack->size;
    int i;

    for (i=0; i<size; i++) {
        printf(" %d\n", stack->states[i]->state_id);
    }
}
