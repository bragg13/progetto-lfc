#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"
#include "nfa.h"


int init_set(Set* _set, unsigned int _size, const char *name) {
    // set settings
    _set->size = _size;
    _set->length = 0;
    strcpy(_set->name, name);

    // allocate head as a null node
    _set->states = malloc (sizeof(State)*_size);
    return SET_SUCCESS;
}


/**
 * Union operation.
*/
int set_union(Set *res_set, Set *_set1, Set *_set2) {
    printf("starting set_union.\n");

    // iterate through first set
    int i;
    res_set->length = 0;
    res_set->size = _set1->size + _set2->size;
    
    for (i=0; i<_set1->length; i++) {
        set_add_element(res_set, _set1->states[i]);
    }
    for (i=0; i<_set2->length; i++) {
        set_add_element(res_set, _set2->states[i]);
    }
    
    printf("Union performed. Done.\n");
    return SET_SUCCESS;
}

/**
 * Intersection operation.
 */
int set_intersection(Set *res_set, Set *_set1, Set *_set2) {
    printf("starting set_intersection.\n");

    if (res_set == NULL) {
        return -1;
    }

    // iterate through first set
    int i;
    for (i=0; i<_set1->length; i++) {
        State state = _set1->states[i];
        if (set_contains(_set2, state)) {
            set_add_element(res_set, state);
        }
    }

    printf("Intersection performed. Done.\n");
    return SET_SUCCESS;
}

/**
 * Complements operation.
 */
int set_complements();

/**
 * Cartesian product operation.
 */
int set_cartesian_product();


/**
 * Checks if a node is in the set.
 * 
 * Returns:
 *  SET_TRUE if the set contains the element
 *  SET_FALSE if not
 */
int set_contains(Set* _set, State el) {
    printf("starting set_contains.\n");

    // iterate thru list
    int i;
    for (i=0; i<_set->length; i++) {
        if (_set->states[i].state_id == el.state_id) {
            return SET_TRUE;
        }
    }

    printf("element with value not %d found. Done.\n", el.state_id);
    return SET_FALSE;
}

/**
 * Add an element to the set.
 * 
 * Returns:
 *  SET_SUCCESS if the operation was successful
 *  SET_ERROR if there was an error
 */
int set_add_element(Set* _set, State el) {
    printf("starting set_add_element.\n");
    int last_el = _set->length;

    if (_set->length+1 > _set->size) {
        perror("cant add an element, length == size");
        return SET_ERROR;
    }

    if (set_contains(_set, el)) {
        perror("element is already in the set");
        return SET_ERROR;

    } else {
        // iterate through list til the last element
        _set->states[last_el] = el;
        _set->length++;
    }

    printf("added element with value %d. Done.\n", el.state_id);
    return SET_SUCCESS;
}


int set_remove_element(Set* _set, State* el) {
    printf("starting set_remove_element.\n");

    perror("Element with value %d not found.");
    return SET_ERROR;

}

int set_print(Set* _set) {
    printf("\n%s: {", _set->name);

    // iterate through list
    int i;
    for (i=0; i<_set->length; i++) {
        State node = _set->states[i];
        printf(" %d", node.state_id);
    }

    printf(" }");

    return SET_SUCCESS;
}