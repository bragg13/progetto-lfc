#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "set.h"
#include "thompson_construction.h"
#include "state_stack.h"
#include "reg_exp.h"
#define NUMBER_ALPHABET_SYMBOLS 10

int main(int argc, char **argv) {
    // get input
    char *str = get_input();
    printf("%s\n", str);

    // add explicit concatenation to input string
    str = add_explicit_concat(str);
    printf("%s\n", str);


    // char str_c[strlen(str)*2];
    
    // printf("%s [%d]\n", str_c, strlen(str_c));
    // char str_p[strlen(str_c)];

    // infix_to_postfix(str_c, str_p);
    printf("\n");
    return 0;
}