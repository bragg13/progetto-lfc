#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "thompson_construction.h"
#include "reg_exp.h"

int main(int argc, char **argv) {
    // get input
    char *str = get_input();
    printf("%s\n", str);

    // add explicit concatenation to input string
    str = add_explicit_concat(str);
    printf("%s\n", str);

    // transform the expression to postfix
    str = infix_to_postfix(str);
    printf("%s\n", str);

    // construct the NFA
    NFA *final_nfa = nfa_build(str);
    nfa_print(final_nfa);

    // write output
    write_output(final_nfa);

    // free up memory
    

    printf("\n");
    return 0;
}


// TODO: if a number is in input is converted to char