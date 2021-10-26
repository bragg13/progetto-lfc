#ifndef PROGETTO_SUBSET_CONSTRUCTION_H
#define PROGETTO_SUBSET_CONSTRUCTION_H

#include <stdio.h>
#include <stdlib.h>
#define N 10
#define SC_ERROR -1
#define SC_SUCCESS 1
#define SC_TRUE 1
#define SC_FALSE 0

enum state_t {INITIAL=0, DEFAULT=1, FINAL=2} state_t;

/* define structures */
typedef struct Graph {
    struct State *states;      // array of pointers to represent adjacency list
    int states_no;
} Graph;

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
void get_input(Graph *nfa);

// void translateInput();


/* function prototypes */
void print_nfa(Graph *nfa);

void eps_closure();

int free_memory(Graph *nfa);


#endif //PROGETTO_SUBSET_CONSTRUCTION_H
