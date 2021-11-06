#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
// #include "set.h"
#include "thompson_construction.h"
// #include "state_stack.h"
#include "reg_exp.h"
#define NUMBER_ALPHABET_SYMBOLS 10

int main(int argc, char **argv) {
    // get input
    char *str = get_input();
    printf("%s\n", str);

    // add explicit concatenation to input string
    str = add_explicit_concat(str);
    printf("%s\n", str);

    // transform the xpression to postfix
    str = infix_to_postfix(str);
    printf("%s\n", str);

    // construct the NFA
    NFA *final_nfa = nfa_build(str);
    nfa_print(&final_nfa);

    printf("\n");
    return 0;
}