#include <stdio.h>
#include <stdlib.h>
#include "thompson_construction.h"
#include "nfa.h"
#include "string.h"
#include "int_stack.h"
#include "nfa_stack.h"

int state_id = 0;

// TODO: deallocate old states when creating a new one. possible only if i create new states for the result, should i?


char* get_input() {
    FILE *fp;
    int length;

    fp = fopen("input.txt", "r");
    if (fp == NULL) {
        perror("Failed opening file");
        return NULL;
    }

    fscanf(fp, "%d", &length);

    if (length <= 0) {
        perror("Length cant be 0 or less");
        return NULL;
    }

    char *str = malloc(sizeof(char)*length+1);
    fscanf(fp, "%s", str);
    fclose(fp);

    str[length] = '\0';

    // check if letters/numbers
    int i=0;
    char c;
    for (i; i<length; i++) {
        c = (char) str[i];
        if ( (c>='A' && c<='Z') || (c>='a' && c<='z') || (c>='0' && c<='9') || c=='(' || c==')' || c=='|' || c=='.' || c=='*') {
            continue;
        }
        printf("char: %c\n", c);
        perror("found an invalid character in the alphabet\n");
        return NULL;
    }

    return str;
}

NFA* nfa_build(char *reg_exp) {
    // il massimo numero di stati che puo avere e' 2k dove k e' il numero di simboli
    int i;
    char symbol;

    NfaStack *nfa_stack = init_nfa_stack(strlen(reg_exp));
    NFA *temp1 = malloc(sizeof(NFA)); temp1 = NULL;
    NFA *temp2 = malloc(sizeof(NFA)); temp2 = NULL;
    NFA *final;

    // iterate through the regular expression
    for (i=0; i<strlen(reg_exp); i++) {
        symbol = reg_exp[i];
        
        if (symbol == '|') {
            // double pop from the stack, apply operation and push the result to stack
            temp1 = nfa_stack_pop(nfa_stack);
            temp2 = nfa_stack_pop(nfa_stack);
            NFA *temp = nfa_union(temp2, temp1);
            nfa_stack_push(nfa_stack, temp);

        } else if (symbol == '.') {
            // double pop from the stack, apply operation and push the result to stack
            temp1 = nfa_stack_pop(nfa_stack);
            temp2 = nfa_stack_pop(nfa_stack);
            NFA *temp = nfa_concat(temp2, temp1);
            nfa_stack_push(nfa_stack, temp);
        
        } else if (symbol == '*') {
            // double pop from the stack, apply operation and push the result to stack
            temp1 = nfa_stack_pop(nfa_stack);
            NFA *temp = nfa_kleene(temp1);
            nfa_stack_push(nfa_stack, temp);
        
        } else {
            // create the nfa and push it to the stack
            NFA *temp = nfa_create(symbol);
            nfa_stack_push(nfa_stack, temp);
            printf("created nfa by character and pushed\n");
            nfa_print(temp);
        }    
    }

    // there's only one element remaining which is the resulting nfa
    return nfa_stack_pop(nfa_stack);
}

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


/*  
    ...
*/
NFA* nfa_concat(NFA *nfa1, NFA *nfa2) {
    // creating the resulting NFA
    int result_states_no = nfa1->states_no + nfa2->states_no;
    int result_trans_no = nfa1->trans_no + nfa2->trans_no+1;
    NFA *result = nfa(result_states_no, result_trans_no);

    /* ===== STATES ===== */
    // copy nfa states into result states
    int i, j=0;
    for (i=0; i<nfa1->states_no; i++) {
        result->states[j++] = nfa1->states[i];
    }
    for (i=0; i<nfa2->states_no; i++) {
        // not adding nfa2 initial state since it's the same as nfa1 final
        // if (nfa2->states[i] == nfa2->final_state) {
        //     continue;
        // }
        result->states[j++] = nfa2->states[i];
    }

    /* ===== EDGES ===== */
    // copy nfa transitions into result transitions
    j=0;
    for (i=0; i<nfa1->trans_no; i++) {
        result->transitions[j++] = nfa1->transitions[i];
    }
    for (i=0; i<nfa2->trans_no; i++) {
        result->transitions[j++] = nfa2->transitions[i];
        
        // if (nfa2->transitions[i] == nfa2->initial_state) {
        //     result->transitions[j-1]->src = nfa1->final_state;
        // }
    }

    // create new epsilon transition
    // - connect nfa1.final to nfa2.initial
    Edge *e = edge(nfa1->final_state, nfa2->initial_state, 'e');
    result->transitions[j] = e;

    // result.initial is now nfa1.inital
    result->initial_state = nfa1->initial_state;

    // result.final is now nfa2.final
    result->final_state = nfa2->final_state;

    return result;
}

/*
    ...
*/
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
    Edge *e1 = edge(result->initial_state, nfa1->initial_state, 'e');
    result->transitions[j++] = e1;
    
    // - connect result.initial to nfa2.initial
    Edge *e2 = edge(result->initial_state, nfa2->initial_state, 'e');
    result->transitions[j++] = e2;

    // - connect nfa1.final to result.final
    Edge *e3 = edge(nfa1->final_state, result->final_state, 'e');
    result->transitions[j++] = e3;
    
    // - connect nfa2.final to result.final
    Edge *e4 = edge(nfa2->final_state, result->final_state, 'e');
    result->transitions[j++] = e4;
    
    return result;
}

/*
    ...
*/
NFA* nfa_kleene(NFA *_nfa) {
    // creating the resulting nfa
    int result_states_no = _nfa->states_no + 2;       // adding two more states
    int result_trans_no = _nfa->trans_no + 4;            // adding four more transitions
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
    Edge *e1 = edge(result->initial_state, _nfa->initial_state, 'e');
    result->transitions[j++] = e1;
    
    // - connect new.initial to new.final
    Edge *e2 = edge(result->initial_state, result->final_state, 'e');
    result->transitions[j++] = e2;
    
    // - connect nfa.final to nfa.inital
    Edge *e3 = edge(_nfa->final_state, _nfa->initial_state, 'e');
    result->transitions[j++] = e3;
    
    // - connect nfa.final to new.final
    Edge *e4 = edge(_nfa->final_state, result->final_state, 'e');
    result->transitions[j++] = e4;

    return result;
}
