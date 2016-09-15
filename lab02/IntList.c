#include <stdlib.h>
#include <stdio.h>
#include "IntList.h"

// validate if the malloc has not failed
void validate_malloc(void *pointer) {
    if (pointer == NULL) {
        printf("Out of memory");
        exit(1);
    }
}

IntList *create_list() {
    IntList *new_list = malloc(sizeof(IntList));

    validate_malloc(new_list);

    new_list->first = NULL;

    return new_list;
}

void free_list(IntList *list) {
    Node *next, *current = list->first;

    // free all nodes from list
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    free(list);
}

void add_to_list(IntList *list, int value) {
    Node *current_node;
    Node *new_node = malloc(sizeof(Node));

    validate_malloc(new_node);

    new_node->value = value;
    new_node->next = NULL;
    new_node->previous = NULL;

    if (list->first == NULL) { // if list is empty
        list->first = new_node;
    } else {
        current_node = list->first;

        while (current_node->next != NULL) { // find last node from list
            current_node = current_node->next;
        }

        current_node->next = new_node; // put new value in the end of the list
        new_node->previous = current_node;
    }
}

// removes from the list returning the cost of the operation
int remove_with_cost(IntList *list, int value) {
    int cost = 1;
    Node *current_node;


    if (list->first->value == value) { // if list is empty
        if (list->first->next != NULL) {
            list->first = list->first->next;
            free(list->first->previous);
            list->first->previous = NULL;
        } else {
            free(list->first);
            list->first = NULL;
        }
    } else {
        current_node = list->first;

        while (current_node != NULL && current_node->value != value) { // find node to be deleted
            cost++;
            current_node = current_node->next;
        }

        if (current_node != NULL) {
            current_node->previous->next = current_node->next;
            if (current_node->next != NULL) {
                current_node->next->previous = current_node->previous;
            }

            free(current_node);
        }
    }

    return cost;
}

// access the list applying mtf and returning the cost of the operation
int mtf_access(IntList *list, int value) {
    int cost = 1;
    Node *current_node = list->first;

    if (current_node->value == value) {
        return 1;
    }

    // while did not find the value
    while (current_node->next != NULL && current_node->value != value) {
        cost++;
        current_node = current_node->next;
    }

    // remove the node from the list
    current_node->previous->next = current_node->next;

    if (current_node->next != NULL) {
        current_node->next->previous = current_node->previous;
    }

    // add the node to the end of the list
    current_node->next = list->first;
    list->first->previous = current_node;
    list->first = current_node;

    return cost;
}

// adds to the list returning the cost of the operation
int mtf_add(IntList *list, int value) {
    int cost = 1;
    Node *current_node;
    Node *new_node = malloc(sizeof(Node));

    validate_malloc(new_node);

    new_node->value = value;
    new_node->next = NULL;
    new_node->previous = NULL;

    if (list->first == NULL) { // if list is empty
        list->first = new_node;
    } else {
        current_node = list->first;

        while (current_node->next != NULL) { // find last node from list
            cost++;
            current_node = current_node->next;
        }

        current_node->next = new_node; // put new value in the end of the list
        new_node->previous = current_node;
    }

    return cost + 1;
}



void transpose(Node *node, IntList *list) {
    Node *aux_node;
    node->previous->next = node->next;

    if (node->next != NULL) {
        node->next->previous = node->previous;
    }

    node->next = node->previous;

    if (node->previous != list->first){

        node->previous->previous->next = node;
        aux_node = node->previous;
        node->previous = node->previous->previous;
        aux_node->previous = node;
    } else {
        list->first->previous = node;
        node->previous = NULL;
        list->first = node;
    }
}

int tr_access(IntList *list, int value) {
    int cost = 1;
    Node *current_node = list->first;

    if (current_node->value == value) {
        return 1;
    }

    while (current_node->next != NULL && current_node->value != value) {
        cost++;
        current_node = current_node->next;
    }

    transpose(current_node, list);

    return cost;
}

int tr_add(IntList *list, int value) {
    int cost = 1;
    Node *current_node;
    Node *new_node = malloc(sizeof(Node));

    validate_malloc(new_node);

    new_node->value = value;
    new_node->next = NULL;
    new_node->previous = NULL;

    if (list->first == NULL) { // if list is empty
        list->first = new_node;
    } else {
        current_node = list->first;

        while (current_node->next != NULL) { // find last node from list
            cost++;
            current_node = current_node->next;
        }

        current_node->next = new_node; // put new value in the end of the list

        new_node->previous = current_node;

        transpose(new_node, list);
    }

    return cost + 1;
}