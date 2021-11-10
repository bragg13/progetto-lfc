#include "nfa_stack.h"

/* Initializes a stack. */
NfaStack* init_nfa_stack(unsigned int capacity) {
    NfaStack *stack = (NfaStack*) malloc(sizeof(NfaStack));
    stack->capacity = capacity;
    stack->size = 0;
    stack->stack = malloc(sizeof(NFA*)*capacity);
    if (stack == NULL) {
        perror("Error creating stack.\n");
        return NULL;
    }
    return stack;
}

/* Couple of useful functions */ 
int nfa_stack_is_empty(NfaStack *stack) { return (stack->size == 0) ? 1 : 0; }
int nfa_stack_is_full(NfaStack *stack) { return (stack->size == stack->capacity) ? 1 : 0; }

/* Push function - adds nfa to stack */
void nfa_stack_push(NfaStack *stack, NFA *nfa) {
    if (nfa_stack_is_full(stack)) {
        perror("Stack size wouuld exceed capacity.\n");
        return;
    }

    int i = stack->size;
    stack->stack[i] = nfa;
    stack->size++;
}


/* Pop function - pops element from stack */
NFA* nfa_stack_pop(NfaStack *stack) {
    if (nfa_stack_is_empty(stack)) {
        perror("Stack size is 0, cannot pop.\n");
        return NULL;
    } 

    int i = stack->size-1;
    NFA *nfa = stack->stack[i];
    stack->size--;
    return nfa;
}

/* Returns the element at the top without popping it */
NFA* nfa_stack_peek(NfaStack *stack) {
    if (nfa_stack_is_empty(stack)) {
        perror("Stack size is 0, cannot peek.\n");
        return NULL;
    } 

    int i = stack->size-1;
    NFA *nfa = stack->stack[i];
    return nfa;
}


/* Prints a stack structure */
void print_nfa_stack(NfaStack *stack) {
    printf("Stack: size=%d, capacity=%d [nfa]\n", stack->size, stack->capacity);

    int size = stack->size;
    int i;

    for (i=0; i<size; i++) {
        nfa_print(stack->stack[i]);
    }
}
