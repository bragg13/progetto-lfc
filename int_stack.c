#include "int_stack.h"

/* Initializes a stack. */
IntStack* init_int_stack(unsigned int capacity) {
    IntStack *stack = (IntStack*) malloc(sizeof(IntStack));
    stack->capacity = capacity;
    stack->size = 0;
    stack->stack = (int*) malloc(sizeof(int)*capacity);
    if (stack == NULL) {
        perror("Error creating stack.\n");
        return NULL;
    }
    return stack;
}

/* Couple of useful functions */ 
int int_stack_is_empty(IntStack *stack) { return (stack->size == 0) ? 1 : 0; }
int int_stack_is_full(IntStack *stack) { return (stack->size == stack->capacity) ? 1 : 0; }

/* Push function - adds value to stack */
void int_stack_push(IntStack *stack, int num) {
    if (int_stack_is_full(stack)) {
        perror("Stack size wouuld exceed capacity.\n");
        return;
    }

    int i = stack->size;
    stack->stack[i] = num;
    stack->size++;
}


/* Pop function - pops element from stack */
int int_stack_pop(IntStack *stack) {
    if (int_stack_is_empty(stack)) {
        perror("Stack size is 0, cannot pop.\n");
        return -1;
    } 

    int i = stack->size-1;
    int num = stack->stack[i];
    stack->size--;
    return num;
}

/* Returns the element at the top without popping it */
int int_stack_peek(IntStack *stack) {
    if (int_stack_is_empty(stack)) {
        perror("Stack size is 0, cannot peek.\n");
        return -1;
    } 

    int i = stack->size-1;
    int num = stack->stack[i];
    return num;
}


/* Prints a stack structure */
void print_int_stack(IntStack *stack, int is_char) {
    printf("Stack: size=%d, capacity=%d [int]\n", stack->size, stack->capacity);

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
