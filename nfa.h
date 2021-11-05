#ifndef NFA_H
#define NFA_H

#include <stdio.h>
#include <stdlib.h>

#define NFA_ERROR -1
#define NFA_SUCCESS 1
#define NFA_TRUE 1
#define NFA_FALSE 0

/* define structures */
typedef struct NFA {
    struct State *states;      // array of pointers to represent adjacency list
    int states_no;
} NFA;

typedef struct State {
    int state_type;
    int state_id;
    struct Edge *edges;         // how am i supposed to allocate a graph of states if a state has array of edges unallocated? tf
    int edges_no;
} State;

typedef struct Edge {
    int src;
    int dst;
    char val;
} Edge;

#endif // NFA_H
