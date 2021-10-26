#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"

int create_node (nodeptr _node, int _value) {
    _node->next = NULL;
    _node->value = _value;
}


int init_set(set* _set, unsigned int _size, const char *name) {
    // set settings
    _set->size = _size;
    _set->length = 0;
    strcpy(_set->name, name);

    // allocate head as a null node
    _set->head = (node*) malloc (sizeof(node*));
    _set->head->next = NULL;
    _set->head->value = SET_NULL_VALUE;

    return SET_SUCCESS;
}


/**
 * Union operation.
*/
int set_union(set *res_set, set *_set1, set *_set2) {
    printf("starting set_union.\n");

    // iterate through first set
    nodeptr node1 = (_set1->head)->next;
    while (node1 != NULL) {
        nodeptr new_node = (nodeptr) malloc(sizeof(nodeptr)); create_node(new_node, node1->value);
        set_add_element(res_set, new_node);
        node1 = node1->next;
    }

    // iterate through second set
    nodeptr node2 = (_set2->head)->next;
    while (node2 != NULL) {
        nodeptr new_node = (nodeptr) malloc(sizeof(nodeptr)); create_node(new_node, node2->value);
        set_add_element(res_set, new_node);
        node2 = node2->next;
    }

    printf("Union performed. Done.\n");
    return SET_SUCCESS;
}

/**
 * Intersection operation.
 */
int set_intersection(set *res_set, set *_set1, set *_set2) {
    printf("starting set_intersection.\n");

    // iterate through first set
    nodeptr node = (_set1->head)->next;
    while (node != NULL) {
        if (set_contains(_set2, node)) {
            nodeptr new_node = (nodeptr) malloc(sizeof(nodeptr));
            create_node(new_node, node->value);
            set_add_element(res_set, new_node);
        }
        node = node->next;
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
int set_contains(set* _set, node *el) {
    printf("starting set_contains.\n");

    // iterate thru list
    nodeptr node = (_set->head)->next;
    while (node != NULL) {
        if (node->value == el->value) {
            return SET_TRUE;
        }
        node = node->next;
    }

    printf("element with value not %d found. Done.\n", el->value);
    return SET_FALSE;
}

/**
 * Add an element to the set.
 * 
 * Returns:
 *  SET_SUCCESS if the operation was successful
 *  SET_ERROR if there was an error
 */
int set_add_element(set* _set, nodeptr el) {
    printf("starting set_add_element.\n");

    if (_set->length+1 > _set->size) {
        perror("cant add an element, length == size");
        return SET_ERROR;
    }

    if (set_contains(_set, el)) {
        perror("element is already in the set");
        return SET_ERROR;

    } else {
        // iterate through list til the last element
        nodeptr node = _set->head;
        while (node->next != NULL) { node = node->next; }
        node->next = el;                    // connect new element
        el->next = NULL;                    // make sure the new tail is a tail

    }

    printf("added element with value %d. Done.\n", el->value);
    return SET_SUCCESS;
}


int set_remove_element(set* _set, nodeptr el) {
    printf("starting set_remove_element.\n");

    nodeptr node = (_set->head)->next;
    while (node != NULL) {
        if (node->value == el->value) {
            nodeptr next_node = node->next;
            free(next_node);

            printf("removed element with value %d. Done.", el->value);
            return SET_SUCCESS;
        }
        node = node->next;
    }

    perror("Element with value %d not found.");
    return SET_ERROR;

}

int set_to_string(set* _set) {
    printf("\n%s: {", _set->name);

    // iterate through list
    nodeptr node = (_set->head)->next;  // first element, pointed by head
    while (node != NULL) {
        printf(" %d", node->value);
        node = node->next;
    }

    printf(" }");

    return SET_SUCCESS;
}