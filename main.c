#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "set.h"
#include "subset_construction.h"
#include "stack.h"

int main(int argc, char **argv) {
    // set A, B, C, D;          // TODO: replace A, B, C with *A, *B, *C then remove &
    // init_set(&A, 2, "A");
    // init_set(&B, 4, "B");
    // init_set(&C, 5, "C");
    // init_set(&D, 5, "D");

    // // fill A
    // int i;
    // for (i=0; i<2; i++) {
    //     node* _node = (node*) malloc(sizeof(node*));
    //     create_node(_node, i);
    //     set_add_element(&A, _node);
    // }

    // // fill B
    // for (i=2; i<6; i++) {
    //     node* _node = (node*) malloc(sizeof(node*));
    //     create_node(_node, i);
    //     set_add_element(&B, _node);
    // }

    // // fill C
    // set_union(&C, &A, &B);

    // // fill D
    // set_intersection(&D, &A, &C);

    // set_to_string(&A);
    // set_to_string(&B);
    // set_to_string(&C);
    // set_to_string(&D);

    // printf("\n\n\n");

    // Graph nfa;
    // get_input(&nfa);
    // print_nfa(&nfa);
    
    Stack stack;
    init_stack(&stack, 5);
    print_stack(&stack);

    State a, b, *c;
    a.state_id = 0;
    b.state_id = 12;

    push(&stack, &a);
    push(&stack, &b);
    
    print_stack(&stack);

    c = pop(&stack);

    print_stack(&stack);
    return 0;
}