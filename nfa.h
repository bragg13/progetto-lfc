#ifndef NFA_H
#define NFA_H

#include <stdio.h>
#include <stdlib.h>
#define NFA_ERROR -1
#define NFA_SUCCESS 1
#define NFA_TRUE 1
#define NFA_FALSE 0

enum state_t {INITIAL=0, DEFAULT=1, FINAL=2} state_t;

/* define structures */
typedef struct NFA {
    struct State *states;      // array of pointers to represent adjacency list
    int states_no;
} NFA;

typedef struct State {
    enum state_t state_type;
    int state_id;
    struct Edge *edges;         // how am i supposed to allocate a graph of states if a state has array of edges unallocated? tf
    int edges_no;
} State;

typedef struct Edge {
    int src;
    int dst;
    int val;                    // TODO: should not be limited to int
} Edge;


/* input management */
void get_input(NFA *nfa);

// void translateInput();


/* function prototypes */
void print_nfa(NFA *nfa);

int free_memory(NFA *nfa);


#endif // NFA_H
