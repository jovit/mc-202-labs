#include <stdlib.h>
#include <stdio.h>
#include "IntList.h"
#include "Utils.h"

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

    if (list->first == NULL) { // if list is empty
        list->first = new_node;
    } else {
        current_node = list->first;

        while (current_node->next != NULL) { // find last node from list
            current_node = current_node->next;
        }
        current_node->next = new_node; // put new value in the end of the list
    }
}

char list_contains(IntList *list, int key) {
    Node *current_node;

    current_node = list->first;
    while (current_node != NULL) {
        if (current_node->value == key) {
            return 1;
        }
        current_node = current_node->next;
    }

    return 0;
}

void remove_from_list(IntList *list, int key) {
    Node *current_node;
    Node *node_to_delete;

    if (list->first->value == key) {
        node_to_delete = list->first;
        list->first = list->first->next;
    } else {
        current_node = list->first;

        while (current_node->next != NULL) { // find last node from list
            if (current_node->next->value == key) {
                node_to_delete = current_node->next;
                current_node->next = current_node->next->next;
            }
        }
    }

    free(node_to_delete);
}

