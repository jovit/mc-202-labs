#include <stdlib.h>
#include <stdio.h>
#include "MallocUtils.h"
#include "MatrioshkaList.h"

MatrioshkaList *new_list() {
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
        free(current->matrioshka);
        free(current);
        current = next;
    }

    free(list);
}

char add_to_list(MatrioshkaList *list, Matrioshka *matrioshka) {
    ListNode *current_node;
    ListNode *new_node = malloc(sizeof(ListNode));

    validate_malloc(new_node);

    new_node->matrioshka = matrioshka;
    new_node->next = NULL;

    if (list->first == NULL) { // if list is empty
        list->first = new_node;
    } else if (list->first->matrioshka->value > matrioshka->value) { // if should be the first element
        new_node->next = list->first;
        list->first = new_node;
    } else if (list->first->matrioshka->value == matrioshka->value) { // if the first matrioshka has the same value
        free(new_node);

        if (list->first->matrioshka->color != matrioshka->color) { // if they have different colors, it fails to add
            return 0;
        }
    } else {
        current_node = list->first;

        while (current_node->next != NULL
            && current_node->next->matrioshka->value < new_node->matrioshka->value) { // find place to add the matrioshka
            
            current_node = current_node->next;
        }

        // if the next matrioshka is the same as the one being added
        if (current_node->next != NULL && current_node->next->matrioshka->value == matrioshka->value) {
            free(new_node);
            // checks if the color is the same
            if (current_node ->next->matrioshka->color != matrioshka->color) {
                return 0;
            }
        } else { // else add the value to the correct position in the list
            new_node->next = current_node->next;
            current_node->next = new_node;
        }

    }
    return 1; // successfully added the matrioshka
}