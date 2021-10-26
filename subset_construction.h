#ifndef PROGETTO_SUBSET_CONSTRUCTION_H
#define PROGETTO_SUBSET_CONSTRUCTION_H

typedef struct nfa *NFA;

struct nfa {
    int n;                      // number of states
    struct state *stateList;    // states
};

typedef struct state {
    int value;
    struct state *next;
    char type[3];       // FINal | BEGin | DEFault
} state;



#endif //PROGETTO_SUBSET_CONSTRUCTION_H
