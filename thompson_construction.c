#include "thompson_construction.h"

int state_id = 0;

/* Reads input file and returns the string in it */
char* get_input(char *input_str) {
    FILE *fp;
    int length;

    // open the file
    fp = fopen(input_str, "r");
    if (fp == NULL) {
        perror("Failed opening file");
        exit(-1);
    }

    // read string length
    fscanf(fp, "%d", &length);
    if (length <= 0) {
        perror("Length cant be 0 or less");
        return NULL;
    }

    // read the actual string
    char *str = malloc(sizeof(char)*length+1);
    fscanf(fp, "%s", str);
    fclose(fp);

    // set string terminator
    str[length] = '\0';

    // check if string has bad characters in it
    int i=0;
    char c;
    for (i; i<length; i++) {
        c = (char) str[i];
        if ( (c>='A' && c<='Z') || (c>='a' && c<='z') || (c>='0' && c<='9') || 
            c=='(' || c==')' || c=='|' || c=='.' || c=='*' || c=='#') {
            continue;
        }
        perror("found an invalid character in the alphabet\n");
        return NULL;
    }

    return str;
}

/* Write NFA to output file */
void write_output(NFA *nfa, char *output_str, int output_type) {
    FILE *fp;
    int i;

    // open the file
    fp = fopen(output_str, "w");
    if (fp == NULL) {
        perror("Failed opening file");
        return;
    }

    if (output_type == 0) {
        // initial/final states
        fprintf(fp, "%d %d\n", nfa->initial_state, nfa->final_state);
        
        // states
        for (i=0; i<nfa->states_no; i++) {
            fprintf(fp, "%d ", nfa->states[i]);
        }
        fprintf(fp, "\n");

        // transitions
        for (i=0; i<nfa->trans_no; i++) {
            Edge *e = nfa->transitions[i];
            fprintf(fp, "%d %d %c\n", e->src, e->dst, e->val);
        }
    } else {
        // prints to file the nfa
        fprintf(fp, "========== OUTPUT NFA ==========\n");
        fprintf(fp, "| Initial state: %d\n| Final state: %d\n", nfa->initial_state, nfa->final_state);
        
        fprintf(fp, "| States: [ ");
        for (i=0; i<nfa->states_no; i++) {
            fprintf(fp, "%d ", nfa->states[i]);
        }
        fprintf(fp, "]\n");
        fprintf(fp, "| Transitions: \n");
        
        for (i=0; i<nfa->trans_no; i++) {
            Edge *e = nfa->transitions[i];
            fprintf(fp, "| %d -- %c --> %d\n", e->src, e->val, e->dst);
        }

        fprintf(fp, "================================\n");
    }

    fclose(fp);
}

/* Given a string, parse it and through Thompson Construction builds an nfa */
NFA* nfa_build(char *reg_exp) {
    NfaStack *nfa_stack = init_nfa_stack(strlen(reg_exp));
    NFA *temp1 = malloc(sizeof(NFA)); temp1 = NULL;
    NFA *temp2 = malloc(sizeof(NFA)); temp2 = NULL;
    int i;
    char symbol;

    // iterate through the regular expression
    for (i=0; i<strlen(reg_exp); i++) {
        symbol = reg_exp[i];
        
        if (symbol == '|') {
            // double pop from the stack, apply union and push the result to stack
            temp1 = nfa_stack_pop(nfa_stack);
            temp2 = nfa_stack_pop(nfa_stack);
            NFA *temp = nfa_union(temp2, temp1);
            nfa_stack_push(nfa_stack, temp);

        } else if (symbol == '.') {
            // double pop from the stack, apply concatenation and push the result to stack
            temp1 = nfa_stack_pop(nfa_stack);
            temp2 = nfa_stack_pop(nfa_stack);
            NFA *temp = nfa_concat(temp2, temp1);
            nfa_stack_push(nfa_stack, temp);
        
        } else if (symbol == '*') {
            // double pop from the stack, apply kleene star and push the result to stack
            temp1 = nfa_stack_pop(nfa_stack);
            NFA *temp = nfa_kleene(temp1);
            nfa_stack_push(nfa_stack, temp);
        
        } else {
            // create a symbol nfa and push it to the stack
            NFA *temp = nfa_create(symbol);
            nfa_stack_push(nfa_stack, temp);
        }    
    }

    // there's only one element remaining in the stack, which is our resulting nfa
    return nfa_stack_pop(nfa_stack);
}

/* Creates an nfa starting given the transition symbol */
NFA* nfa_create(char symbol) {
    // create NFA
    NFA *_nfa = nfa(2, 1);

    // ids for creating edge
    int initial_id = state_id++;
    int final_id = state_id++;

    _nfa->states[0] = initial_id;
    _nfa->states[1] = final_id;

    // create edge between states
    Edge *_edge = edge(initial_id, final_id, symbol);
    
    // put stuff together
    _nfa->transitions[0] = _edge;
    _nfa->initial_state = initial_id;
    _nfa->final_state = final_id;
}


/* Concatenates two nfas into a new one */
NFA* nfa_concat(NFA *nfa1, NFA *nfa2) {
    // create the resulting NFA
    int result_states_no = nfa1->states_no + nfa2->states_no - 1;
    int result_trans_no = nfa1->trans_no + nfa2->trans_no;
    NFA *result = nfa(result_states_no, result_trans_no);

    // the merged state and those to merge
    int merged_state = state_id++;
    int final_state1 = nfa1->final_state;
    int initial_state2 = nfa2->initial_state;

    /* ===== STATES ===== */
    // copy nfa states into result states
    int i, j=0;
    for (i=0; i<nfa1->states_no; i++) {
        if (nfa1->states[i] == final_state1) {
            continue;       // don't copy the merged state
        } 
        result->states[j++] = nfa1->states[i];
    }
    for (i=0; i<nfa2->states_no; i++) {
        if (nfa2->states[i] == initial_state2) {
            continue;       // don't copy the merged state
        } 
        result->states[j++] = nfa2->states[i];
    }
    // add merged state
    result->states[j++] = merged_state;

    /* ===== EDGES ===== */
    // copy nfa transitions into result transitions
    j=0;
    for (i=0; i<nfa1->trans_no; i++) {
        // if src/dst are the old final state, change them to the new one
        if (nfa1->transitions[i]->src == final_state1) {
            nfa1->transitions[i]->src = merged_state;
        }
        if (nfa1->transitions[i]->dst == final_state1) {
            nfa1->transitions[i]->dst = merged_state;
        }
        
        result->transitions[j++] = nfa1->transitions[i];
    }
    for (i=0; i<nfa2->trans_no; i++) {
        // if src/dst are the old initial state, change them to the new one
        if (nfa2->transitions[i]->src == initial_state2) {
            nfa2->transitions[i]->src = merged_state;
        }
        if (nfa2->transitions[i]->dst == initial_state2) {
            nfa2->transitions[i]->dst = merged_state;
        }
        result->transitions[j++] = nfa2->transitions[i];
    }

    // result.initial is now nfa1.inital
    result->initial_state = nfa1->initial_state;

    // result.final is now nfa2.final
    result->final_state = nfa2->final_state;

    return result;
}

/* Performs union operation between nfa1 and nfa2 */
NFA* nfa_union(NFA *nfa1, NFA *nfa2) {
    // creating the resulting nfa
    int result_states_no = nfa1->states_no + nfa2->states_no + 2;       // adding two more states
    int result_trans_no = nfa1->trans_no + nfa2->trans_no+4;            // adding four more transitions
    NFA *result = nfa(result_states_no, result_trans_no);

    /* ===== STATES ===== */
    // copy nfa states into result states
    int i, j=0;
    for (i=0; i<nfa1->states_no; i++) {
        result->states[j++] = nfa1->states[i];
    }
    for (i=0; i<nfa2->states_no; i++) {
        result->states[j++] = nfa2->states[i];
    }

    // create new initial state for result nfa
    result->states[j++] = state_id;
    result->initial_state = state_id++;

    // create new final state for result nfa
    result->states[j++] = state_id;
    result->final_state = state_id++;
    
    /* ===== EDGES ===== */
    // copy nfa transitions into result transitions
    j=0;
    for (i=0; i<nfa1->trans_no; i++) {
        result->transitions[j++] = nfa1->transitions[i];
    }
    for (i=0; i<nfa2->trans_no; i++) {
        result->transitions[j++] = nfa2->transitions[i];
    }


    // create 4 epsilon transitions
    // - connect result.initial to nfa1.initial
    Edge *e1 = edge(result->initial_state, nfa1->initial_state, '#');
    result->transitions[j++] = e1;
    
    // - connect result.initial to nfa2.initial
    Edge *e2 = edge(result->initial_state, nfa2->initial_state, '#');
    result->transitions[j++] = e2;

    // - connect nfa1.final to result.final
    Edge *e3 = edge(nfa1->final_state, result->final_state, '#');
    result->transitions[j++] = e3;
    
    // - connect nfa2.final to result.final
    Edge *e4 = edge(nfa2->final_state, result->final_state, '#');
    result->transitions[j++] = e4;
    
    return result;
}

/* Performs kleene star operation on nfa */
NFA* nfa_kleene(NFA *_nfa) {
    // creating the resulting nfa
    int result_states_no = _nfa->states_no + 2;             // adding two more states
    int result_trans_no = _nfa->trans_no + 4;               // adding four more transitions
    NFA *result = nfa(result_states_no, result_trans_no);

    /* ===== STATES ===== */
    // copy _nfa states into result
    int i, j=0;
    for (i=0; i<_nfa->states_no; i++) {
        result->states[j++] = _nfa->states[i];
    }

    // create new initial state for result
    result->states[j++] = state_id;
    result->initial_state = state_id++;

    // create new final state for result
    result->states[j++] = state_id;
    result->final_state = state_id++;
    
    /* ===== EDGES ===== */
    // copy edges into result
    j=0;
    for (i=0; i<_nfa->trans_no; i++) {
        result->transitions[j++] = _nfa->transitions[i];
    }

    // create 4 epsilon transitions
    // - connect result.initial to nfa.initial
    Edge *e1 = edge(result->initial_state, _nfa->initial_state, '#');
    result->transitions[j++] = e1;
    
    // - connect new.initial to new.final
    Edge *e2 = edge(result->initial_state, result->final_state, '#');
    result->transitions[j++] = e2;
    
    // - connect nfa.final to nfa.inital
    Edge *e3 = edge(_nfa->final_state, _nfa->initial_state, '#');
    result->transitions[j++] = e3;
    
    // - connect nfa.final to new.final
    Edge *e4 = edge(_nfa->final_state, result->final_state, '#');
    result->transitions[j++] = e4;

    return result;
}
