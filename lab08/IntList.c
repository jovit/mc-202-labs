#include <wchar.h>
#include <stdlib.h>
#include "IntList.h"
#include "Utils.h"

IntList *create_list() {
    IntList *new_list = malloc(sizeof(IntList));
    validate_malloc(new_list);

    new_list->root = NULL;

    return new_list;
}

void add_to_start(IntList *list, int value) {
    IntListNode *new_node;

    new_node = malloc(sizeof(IntListNode));
    validate_malloc(new_node);

    new_node->value = value;
    new_node->next = list->root;

    list->root = new_node;
}

int get(IntList *list, int index) {
    IntListNode *current = list->root;
    int i;

    for (i = 0; i < index && current != NULL; i++) {
        current = current->next;
    }

    if (current == NULL) {
        return -1;
    }

    return current->value;
}

void free_list(IntList *list) {
    IntListNode *current_node;
    current_node = list->root;

    while (current_node != NULL) {
        list->root = list->root->next;
        free(current_node);
        current_node = list->root;
    }

    free(list);
}
