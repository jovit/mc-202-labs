#include <stdlib.h>
#include <stdio.h>
#include "MatrioshkaList.h"

// validate if the malloc has not failed
void validate_malloc(void *pointer) {
    if (pointer == NULL) {
        printf("Out of memory");
        exit(1);
    }
}

MatrioshkaList *create_list() {
    MatrioshkaList *new_list = malloc(sizeof(MatrioshkaList));

    validate_malloc(new_list);

    new_list->first = NULL;

    return new_list;
}

void free_list(MatrioshkaList *list) {
    ListNode *next, *current = list->first;

    // free all nodes from list
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    free(list);
}

void add_to_list(MatrioshkaList *list, int value) {
    ListNode *current_node;
    ListNode *new_node = malloc(sizeof(ListNode));

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