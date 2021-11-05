#include "reg_exp.h"
#include "set.h"
#include "int_stack.h"

int get_priority(char c) {
    int p;
    switch(c){
        case '*': p=3; break;
        case '.': p=2; break;
        case '|': p=1; break;
        default: p=-1; break;
    }

    return p;
}

/* 
    add '.' to explicit the concatenation operator to regular expressions which may not have it 
    assuming to have an alphabet made of literals/numbers(?), each max 1 character
    Return:
        int - actual output string dimension, useful to reallocate
*/
char* add_explicit_concat(char *str) {
    printf("add_explicit_concat started...\n");
    
    // allocate output string with crazy size, worst case: #dim literals concatenated, aka #dim-1 '.'
    unsigned int dim = strlen(str);
    char *output = (char*) malloc(sizeof(char)*(dim*2));        // DEALLOC
    
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
                if (next_char == '|' || next_char == '.' || next_char == ')' || next_char == '*') {
                    output[j] = str[i];
                    j++;
                } else {
                    // it's a literal or (, then let's add the '.'
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
    free(str);      // cancello la stringa che ho creato prima perche ritorno quella nuova con la lunghezza sistemata
    
    printf("add_explicit_concat done.\n");
    return output;
}


/* 
    convert regular expression to postfix reverse polish notation 
    the algorithm uses a stack, where I push symbols
    and what is called dst_str represents my output queue
*/
void infix_to_postfix(char *src_str, char *dst_str) {
    // string size
    int src_dim = strlen(src_str);

    // operator stack
    IntStack *stack = init_int_stack(src_dim);         // max dimension

    int i, j=0;
    for (i=0; i<src_dim; i++) {
        printf("symboL: %c\n", src_str[i]);

        /* === OPERATOR ==== */
        if (src_str[i] == '|' || src_str[i] == '.' || src_str[i] == '*') {

            /* === SYMBOL && LEFT PARENTHESIS ON STACK === */
            if ( !int_stack_is_empty(stack) && ((char)int_stack_peek(stack))=='(' ) {

                // push the symbol onto the stack
                dst_str[j++] = src_str[i];
            }

            /* === LESS PRIORITY ==== */
            int priority = get_priority(src_str[i]);
            while (!int_stack_is_empty(stack) && get_priority(int_stack_peek(stack)) >= priority ) {

                // remove the operator from the top of the operator stack and append it to the output queue. 
                char popped_operator = (char) int_stack_pop(stack);
                printf("theres an op with more priority: %c\n", popped_operator);
                dst_str[j++] = popped_operator;
            
            }

            printf("no more op with more priority, pushing this one\n");
            int_stack_push(stack, src_str[i]);
        }

        /* === SYMBOL IS ( === */
        else if (src_str[i] == '(') {
            // ... push it to operator stack
            int_stack_push(stack, '(');

        }

        /* === SYMBOL IS ) === */
        else if (src_str[i] == ')') {
            // ... pop all the operators to output queue till a (
            while (int_stack_is_empty(stack)!=1 && int_stack_peek(stack) != '(' ) {
                char popped_operator = (char) int_stack_pop(stack);
                dst_str[j++] = popped_operator;
            }

            // now i have to remove the ( too
            int_stack_pop(stack);
        }

        /* === LETTER === */
        else {
            dst_str[j++] = src_str[i];
        }

        print_int_stack(stack, 1);
        printf("===\n");
    }
    

    // pop all the remaining operators
    for (i=0; i<stack->size; i++) {
        char popped_operator = (char) int_stack_pop(stack);
        dst_str[j++] = popped_operator;
    }

    // add string terminator
    dst_str[src_dim] = '\0';
    printf("%s", dst_str);

    

}
