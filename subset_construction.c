#include <stdio.h>
#include <stdlib.h>
#include "subset_construction.h"

void get_input(Graph *nfa) {
    FILE *fp;
    int states_no;      // number of states
    int edges_no;       // number of edges
    int initial_no;     // number of initial states
    int default_no;     // number of default states
    int final_no;       // number of final states


    // file open
    fp = fopen("input.txt", "r");
    if (fp == NULL) {
        perror("Failed opening file");
        // return SC_ERROR;
    }

    // number of states and edges - TODO: could calculate
    fscanf(fp, "%d %d", &states_no, &edges_no);
    nfa->states = malloc(sizeof(State)*states_no);    // allocate an array of states ie the nfa
    nfa->states_no = states_no;

    // number of edges per state + state type
    int i;
    int state_edges_no, state_type;
    for (i=0; i<states_no; i++) {
        fscanf(fp, "%d %d", &state_edges_no, &state_type);

        nfa->states[i].edges = malloc(sizeof(Edge)*state_edges_no);
        nfa->states[i].state_id = i;
        nfa->states[i].state_type = state_type;     // conversion to enum should work
        nfa->states[i].edges_no = 0;
    }

    // edges
    int src, dst, val;
    for (i=0; i<edges_no; i++) {
        fscanf(fp, "%d %d %d", &src, &dst, &val);
        int curr_edge_no = nfa->states[src].edges_no;        // 'cen' ie the first empty edge
        nfa->states[src].edges[curr_edge_no].src = src;     // get 'cen' edge of node 'src' and set it up
        nfa->states[src].edges[curr_edge_no].dst = dst;
        nfa->states[src].edges[curr_edge_no].val = val;
        nfa->states[src].edges_no++;                         // increment since just set up an edge
    }

    fclose(fp);
}

void print_nfa(Graph *nfa) {
    printf("\n");
    int i=0;
    int j=0;
    for (i=0; i<nfa->states_no; i++) {
        printf("State: %d\n", i);
        
        for (j=0; j<nfa->states[i].edges_no; j++) {
            Edge e = nfa->states[i].edges[j];
            printf("\t- %d to %d [%d]\n", e.src, e.dst, e.val);
        }
        
        printf("\n");
    }
}
