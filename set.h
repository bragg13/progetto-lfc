#ifndef SET_H
#define SET_H
#include <stdlib.h>
#include <stdio.h>
#include "nfa.h"

#define SET_TRUE 1
#define SET_FALSE 0
#define SET_SUCCESS 1
#define SET_ERROR -1
#define SET_NULL_VALUE -1

typedef struct Set {
    unsigned int size, length;
    char name[10];
    State *states;
} Set;

/**
 * Initializes new Set
*/
int init_set(Set *set, unsigned int size, const char *name);


/**
 * Union operation.
*/ 
int set_union(Set *res_set, Set *set1, Set *set2);

/**
 * Intersection operation.
 */ 
int set_intersection(Set *res_set, Set *set1, Set *set2);

/**
 * Complements operation.
 */
int set_complements();

/**
 * Cartesian product operation.
 */
int set_cartesian_product();


/**
 * Checks if a Node is in the set.
 * 
 * Returns:
 *  SET_TRUE if the set contains the element
 *  SET_FALSE if not
 */
int set_contains(Set *set, State el);

/**
 * Add an element to the set.
 * 
 * Returns:
 *  SET_SUCCESS if the operation was successful
 *  SET_ERROR if there was an error
 */
int set_add_element(Set *set, State el);


int set_remove_element(Set *set, State* el);

int set_to_string(Set *set);

#endif