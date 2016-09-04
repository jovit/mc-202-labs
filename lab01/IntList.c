#include <stdlib.h>
#include <stdio.h>
#include "IntList.h"

void validate_malloc(void *pointer) {
    if (pointer == NULL) {
        printf("Out of memory");
        exit(1);
    }
}

IntList* create_list() {
    IntList *new_list = malloc(sizeof(IntList));

    validate_malloc(new_list);

    new_list->first = NULL;

    return new_list;
}

void free_list(IntList* list) {
    Node *next ,*current = list->first;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    free(list);
}

void add_to_list(IntList* list, int value) {
    Node *current_node;
    Node *new_node = malloc(sizeof(Node));

    validate_malloc(new_node);

    new_node->value = value;

    if (list->first == NULL) {
        list->first = new_node;
    } else {
        current_node = list->first;

        while (current_node->next != NULL) {
            current_node = current_node->next;
        }
        current_node->next = new_node;
    }
}

