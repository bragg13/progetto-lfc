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

    char *str = malloc(sizeof(char)*length+1);      // DEALLOC
    fscanf(fp, "%s", str);
    fclose(fp);

    str[length] = '\0';
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
            temp2 = nfa_stack_pop(nfa_stack);
            NFA *temp = nfa_closure(temp2, temp1);
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


/*  The initial state of N(s) is the initial state of the whole NFA. 
    The final state of N(s) becomes the initial state of N(t). 
    The final state of N(t) is the final state of the whole NFA. 
*/
NFA* nfa_concat(NFA *nfa1, NFA *nfa2) {
    // creating the resulting NFA
    int result_states_no = nfa1->states_no + nfa2->states_no;
    int result_trans_no = nfa1->trans_no + nfa2->trans_no+1;    // adding one more transition
    NFA *result = nfa(result_states_no, result_trans_no);

    // copy nfa1 and nfa2 states into result
    int i, j=0;
    for (i=0; i<nfa1->states_no; i++) {
        result->states[j++] = nfa1->states[i];
    }
    for (i=0; i<nfa2->states_no; i++) {
        result->states[j++] = nfa2->states[i];
    }

    // copy edges into result
    j=0;
    for (i=0; i<nfa1->trans_no; i++) {
        result->transitions[j++] = nfa1->transitions[i];
    }
    for (i=0; i<nfa2->trans_no; i++) {
        result->transitions[j++] = nfa2->transitions[i];
    }

    // create new edge from nfa1.final to nfa2.initial
    Edge *e = edge(nfa1->final_state, nfa2->initial_state, 'e');
    result->transitions[j] = e;

    // initial state of result is the inital state of nfa1
    result->initial_state = nfa1->initial_state;

    // final state of result is the final state of nfa2
    result->final_state = nfa2->final_state;


    // free up old nfas
    // nfa_free(nfa1);
    // nfa_free(nfa2);

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
    // copy nfa1 and nfa2 states into result
    int i, j=0;
    for (i=0; i<nfa1->states_no; i++) {
        result->states[j++] = nfa1->states[i];
    }
    for (i=0; i<nfa2->states_no; i++) {
        result->states[j++] = nfa2->states[i];
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
    for (i=0; i<nfa1->trans_no; i++) {
        result->transitions[j++] = nfa1->transitions[i];
    }
    for (i=0; i<nfa2->trans_no; i++) {
        result->transitions[j++] = nfa2->transitions[i];
    }


    // create 4 epsilon trans - 2 for each new state
    // connect new initial state with nfa1 and nfa2 initial states
    // connect nfa1 and nfa2 final states to new final state
    Edge *e1 = edge(result->initial_state, nfa1->initial_state, 'e');       // res(i)->nfa1(i)
    Edge *e2 = edge(result->initial_state, nfa2->initial_state, 'e');       // res(i)->nfa2(i)
    Edge *e3 = edge(nfa1->final_state, result->final_state, 'e');           // nfa1(f)->res(f)
    Edge *e4 = edge(nfa2->final_state, result->final_state, 'e');           // nfa2(f)->res(f)
    result->transitions[j++] = e1;
    result->transitions[j++] = e2;
    result->transitions[j++] = e3;
    result->transitions[j++] = e4;

    // free up old nfas
    // nfa_free(nfa1);
    // nfa_free(nfa2);

    return result;

}

NFA* nfa_closure() {

}
