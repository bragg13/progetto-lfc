#ifndef PROGETTO_SIMPLE_SET_H
#define PROGETTO_SIMPLE_SET_H

#define SET_TRUE 1
#define SET_FALSE 0
#define SET_SUCCESS 1
#define SET_ERROR -1
#define SET_NULL_VALUE -1

typedef struct node {
    int value;
    struct node* next;
} node;

typedef struct node* nodeptr;

typedef struct set{
    unsigned int size, length;
    char name[10];
    struct node* head;
} set;


/**
 * Creates new node
 */
int create_node (nodeptr _node, int value);

/**
 * Initializes new set
*/
int init_set(set *set, unsigned int size, const char *name);


/**
 * Union operation.
*/ 
int set_union(set *res_set, set *set1, set *set2);

/**
 * Intersection operation.
 */ 
int set_intersection(set *res_set, set *set1, set *set2);

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
int set_contains(set *set, nodeptr el);

/**
 * Add an element to the set.
 * 
 * Returns:
 *  SET_SUCCESS if the operation was successful
 *  SET_ERROR if there was an error
 */
int set_add_element(set* _set, nodeptr el);


int set_remove_element(set* _set, nodeptr el);

int set_to_string(set* _set);

#endif