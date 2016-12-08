#include <wchar.h>
#include <stdlib.h>
#include "LongList.h"
#include "Utils.h"

LongList *create_list() {
    LongList *new_list = malloc(sizeof(LongList));
    validate_malloc(new_list);

    new_list->root = NULL;

    return new_list;
}

void add_to_start(LongList *list, unsigned long value) {
    LongListNode *new_node, *current_node;

    for (current_node = list->root; current_node != NULL; current_node = current_node->next) {
        if (current_node->value == value) {
            current_node->count++;
            break;
        }
    }

    if (current_node == NULL) {
        new_node = malloc(sizeof(LongListNode));
        validate_malloc(new_node);

        new_node->value = value;
        new_node->next = list->root;
        new_node->count = 1;

        list->root = new_node;
    }
}

void free_list(LongList *list) {
    LongListNode *current_node;
    current_node = list->root;

    while (current_node != NULL) {
        list->root = list->root->next;
        free(current_node);
        current_node = list->root;
    }

    free(list);
}

void remove_from_start(LongList *list) {
    LongListNode *item_to_remove;
    if (list->root != NULL) {
        item_to_remove = list->root;
        list->root = list->root->next;

        free(item_to_remove);
    }
}
