#include "reg_exp.h"

/* utils function to get priority of an operator */
int get_priority(char c) {
    int p;
    switch(c){
        case '|': p=1; break;
        case '.': p=2; break;
        case '*': p=3; break;
        default: p=0; break;
    }

    return p;
}

/* adds '.' to explicit the concatenation operator to regular expressions which may not have it */
char* add_explicit_concat(char *str) {
    // allocate output string with worst case size: #dim literals concatenated, aka #dim-1 '.'
    unsigned int dim = strlen(str);
    char *output = (char*) malloc(sizeof(char)*(dim*2));

    int i, j=0;
    for (i=0; i<dim; i++) {
        // add the char to output
        output[j] = str[i];
        j++;
        
        // if an operator, there wont be a concat next
        if (str[i] == '|' || str[i] == '.' || str[i] == '(') {
            continue;
        } 

        // check the next char and if it's a literal too, add the '.'
        if (i != dim-1) {
            char next_char = str[i+1];
            if (next_char == '|' || next_char == '.' || next_char == ')' || next_char == '*') {
                continue;
            } 

            output[j] = '.';
            j++;
        }
    }
    
    // reallocate strings so they match the right size
    output = realloc(output, sizeof(char)*(j+1));
    
    // add string terminator
    output[j] = '\0';
    
    // cancello la stringa che ho creato prima perche ritorno quella nuova con la lunghezza sistemata
    free(str);

    return output;
}


/* convert regular expression to postfix reverse polish notation */
char* infix_to_postfix(char *src_str) {
    // get string size
    int src_dim = strlen(src_str);

    // instantiate new string which will be the dest
    char *dst_str = malloc(sizeof(char)*src_dim+1);

    // create a stack where to put operators
    IntStack *stack = init_int_stack(src_dim);

    // iterate through expression
    int i, j=0;
    for (i=0; i<src_dim; i++) {
        /* === typeof(symbol) = OPERATOR ==== */
        if (src_str[i] == '|' || src_str[i] == '.' || src_str[i] == '*') {

            /* === LEFT PARENTHESIS ON STACK / LESS PRIORITY === */
            int priority = get_priority((char) src_str[i]);
            while (!int_stack_is_empty(stack) && get_priority(int_stack_peek(stack)) >= priority && ((char)int_stack_peek(stack))!='(' ) {

                // remove the operator from the top of the operator stack and append it to the output queue. 
                char popped_operator = (char) int_stack_pop(stack);
                dst_str[j++] = popped_operator;

            }

            // push the operator to stack
            int_stack_push(stack, src_str[i]);

        }

        /* === SYMBOL IS '(' === */
        else if (src_str[i] == '(') {
            // ... push it to operator stack
            int_stack_push(stack, '(');

        }

        /* === SYMBOL IS ')' === */
        else if (src_str[i] == ')') {
            // ... pop all the operators to output queue till a (
            while (int_stack_is_empty(stack)!=1 && int_stack_peek(stack) != '(' ) {
                char popped_operator = (char) int_stack_pop(stack);
                dst_str[j++] = popped_operator;
            }

            // now also pop the ')'
            int_stack_pop(stack);

        }

        /* === LETTER === */
        else {
            dst_str[j++] = src_str[i];
        }
    }
    

    // pop all the remaining operators
    for (i=0; i<stack->size; i++) {
        char popped_operator = (char) int_stack_pop(stack);
        dst_str[j++] = popped_operator;
    }

    // set string terminator
    dst_str[src_dim] = '\0';

    // free old string and return new one
    free(src_str);
    return dst_str;
}
