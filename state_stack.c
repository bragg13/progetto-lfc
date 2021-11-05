#include <stdio.h>
#include <stdlib.h>
#include "state_stack.h"
#include "nfa.h"


/* Initializes a stack. */
StateStack* init_stack(unsigned int capacity) {
    StateStack *stack = (StateStack*) malloc(sizeof(StateStack));
    stack->capacity = capacity;
    stack->size = 0;
    stack->states = (State*) malloc(sizeof(State)*capacity);
    return stack;
}

/* Couple of useful functions */ 
int stack_is_empty(StateStack *stack) { return (stack->size == 0) ? 1 : 0; }
int stack_is_full(StateStack *stack) { return (stack->size == stack->capacity) ? 1 : 0; }

/* Push function to add value to stack */
void stack_push(StateStack *stack, State state) {
    if (stack_is_full(stack)) {
        printf("size > capacity");
        return;
    }

    int i = stack->size;
    stack->states[i] = state;
    stack->size++;
    printf("pushed elemnt with id %d\n", state.state_id);
}


/* Push function to add value to stack */
State stack_pop(StateStack *stack) {
    if (stack_is_empty(stack)) {
        printf("cant pop nothing");
        State s; s.state_id = -1;
        return s;
    } 

    int i = stack->size-1;
    State s = stack->states[i];
    stack->size--;
    return s;
}

/* Prints a stack structure */
void print_stack(StateStack *stack) {
    printf("StateStack: size=%d, capacity=%d\n", stack->size, stack->capacity);

    int size = stack->size;
    int i;

    for (i=0; i<size; i++) {
        printf(" %d\n", stack->states[i].state_id);
    }
}
