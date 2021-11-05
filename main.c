#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "set.h"
#include "nfa.h"
#include "state_stack.h"
#include "reg_exp.h"
#define NUMBER_ALPHABET_SYMBOLS 10

int main(int argc, char **argv) {
    // nfa
    // NFA nfa;
    // get_input(&nfa);
    // print_nfa(&nfa);
    
    // // needed sets
    // Set A;  init_set(&A, NUMBER_ALPHABET_SYMBOLS, "A");     // set of symbols in the alphabet (includes epsilon?)
    // Set S0; init_set(&S0, 10, "S0");                        // initial states nfa
    // Set T0; init_set(&T0, 10, "T0");                        // initial states dfa - initial closure set

    // nfa_get_initial_state(&nfa, &S0);                       // add initial states to set s0
    // set_print(&S0);
    
    // // set t0 to the eps_closure of s0
    // eps_closure(S0.states[0], &nfa, &T0);
    // set_print(&T0);

    char *str = "a(a|b)*b";
    char str_c[strlen(str)*2];
    add_explicit_concat(str, str_c);
    
    printf("%s [%d]\n", str_c, strlen(str_c));
    char str_p[strlen(str_c)];

    infix_to_postfix(str_c, str_p);
    printf("\n");
    return 0;
}