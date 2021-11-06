#include <stdio.h>
#include <stdlib.h>
#include "nfa_stack.h"
#include "nfa.h"


/* Initializes a stack. */
NfaStack* init_nfa_stack(unsigned int capacity) {
    NfaStack *stack = (NfaStack*) malloc(sizeof(NfaStack));
    stack->capacity = capacity;
    stack->size = 0;
    stack->stack = malloc(sizeof(NFA*)*capacity);
    return stack;
}

/* Couple of useful functions */ 
int nfa_stack_is_empty(NfaStack *stack) { return (stack->size == 0) ? 1 : 0; }
int nfa_stack_is_full(NfaStack *stack) { return (stack->size == stack->capacity) ? 1 : 0; }

/* Push function to add value to stack */
void nfa_stack_push(NfaStack *stack, NFA *nfa) {
    if (nfa_stack_is_full(stack)) {
        printf("size > capacity");
        return;
    }

    int i = stack->size;
    stack->stack[i] = nfa;
    stack->size++;
    // printf("pushed elemnt with id %d\n", num);
}


/* Push function to add value to stack */
NFA* nfa_stack_pop(NfaStack *stack) {
    if (nfa_stack_is_empty(stack)) {
        // printf("cant pop nothing");
        return NULL;
    } 

    int i = stack->size-1;
    NFA *nfa = stack->stack[i];
    stack->size--;
    return nfa;
}

/* Returns the element at the top without removing it */
NFA* nfa_stack_peek(NfaStack *stack) {
    if (nfa_stack_is_empty(stack)) {
        // printf("cant peek");
        return NULL;
    } 

    int i = stack->size-1;
    NFA *nfa = stack->stack[i];
    return nfa;
}


/* Prints a stack structure */
void print_nfa_stack(NfaStack *stack) {
    printf("NfaStack: size=%d, capacity=%d\n", stack->size, stack->capacity);

    int size = stack->size;
    int i;

    for (i=0; i<size; i++) {
        nfa_print(stack->stack[i]);
    }
}
