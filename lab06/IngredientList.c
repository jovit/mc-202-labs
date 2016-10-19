#include <stdlib.h>
#include <stdio.h>
#include "IngredientList.h"
#include "Utils.h"

IngredientList *create_ingredient_list() {
    IngredientList *new_list = malloc(sizeof(IngredientList));

    validate_malloc(new_list);

    new_list->first = NULL;

    return new_list;
}

void free_ingredient_list(IngredientList *list) {
    IngredientListNode *next, *current = list->first;

    // free all nodes from list
    while (current != NULL) {
        next = current->next;
        free(current->value);
        free(current);
        current = next;
    }

    free(list);
}

void add_to_ingredient_list(IngredientList *list, Ingredient *value) {
    IngredientListNode *current_node;
    IngredientListNode *new_node = malloc(sizeof(IngredientListNode));

    validate_malloc(new_node);

    new_node->value = value;
    new_node->next = NULL;

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

