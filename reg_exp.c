#include "reg_exp.h"
#include "set.h"
#include "stack.h"

/* 
    add '.' to explicit the concatenation operator to regular expressions which may not have it 
    assuming to have an alphabet made of literals/numbers(?), each max 1 character
    Return:
        int - actual output string dimension, useful to reallocate
*/
void add_explicit_concat(char *str, char *output_str) {
    printf("add_explicit_concat started...\n");
    
    // allocate output string with crazy size, worst case: #dim literals concatenated, aka #dim-1 '.'
    unsigned int dim = strlen(str);
    char *output = (char*) malloc(sizeof(char)*(dim*2));
    
    // TODO: reduce this bloatcode
    int i, j=0;
    for (i=0; i<dim; i++) {
        if (str[i] == '|' || str[i] == '.' || str[i] == '(') {
            // if an operator, just add it to output since there wont be a concat next
            output[j] = str[i];
            j++;

        } else {
            // it's a literal OR ) OR *, hence check the next char and if it's a literal too, add the '.'
            if (i != dim-1) {
                char next_char = str[i+1];
                if (next_char == '|' || next_char == '.' || next_char == '(' || next_char == ')' || next_char == '*') {
                    output[j] = str[i];
                    j++;
                } else {
                    // it's a literal too, then let's add the '.'
                    output[j] = str[i];
                    j++;
                    output[j] = '.';
                    j++;
                }
            } else {
                output[j] = str[i];
                j++;
            }
        }
    }
    
    // realloc strings so they match the right size
    output = realloc(output, sizeof(char)*(j+1));
    strcpy(output_str, output);
    
    printf("add_explicit_concat done.\n");
}


/* 
    convert regular expression to postfix reverse polish notation 
    the algorithm uses a stack, where I push symbols
*/
void infix_to_postfix(char *src_str, unsigned int src_dim, char *dst_str, unsigned int dst_dim) {
    Stack *stack = init_stack(src_dim);         // max dimension

}
