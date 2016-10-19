#include <stdlib.h>
#include <stdio.h>
#include "OrderList.h"
#include "Utils.h"

OrderList *create_order_list() {
    OrderList *new_list = malloc(sizeof(OrderList));

    validate_malloc(new_list);

    new_list->first = NULL;

    return new_list;
}

void free_order_list(OrderList *list) {
    OrderListNode *next, *current = list->first;

    // free all nodes from list
    while (current != NULL) {
        next = current->next;
        free_ingredient_list(current->ingredients);
        free(current);
        current = next;
    }

    free(list);
}

void add_to_order_list(OrderList *list, int order, IngredientList *ingredientList) {
    OrderListNode *current_node;
    OrderListNode *new_node = malloc(sizeof(OrderListNode));

    validate_malloc(new_node);

    new_node->order = order;
    new_node->ingredients = ingredientList;
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

void remove_order(OrderList *list, int order) {
    OrderListNode *current_node;
    OrderListNode *aux;

    current_node = list->first;
    if (list->first != NULL) {
        if (list->first->order == order) {
            aux = list->first;
            list->first = list->first->next;
            free_ingredient_list(aux->ingredients);
            free(aux);
        } else {
            while (current_node->next != NULL) { // find last node from list
                if (current_node->next->order == order) {
                    aux = current_node->next;
                    current_node->next = aux->next;
                    free_ingredient_list(aux->ingredients);
                    free(aux);
                    break;
                }
                current_node = current_node->next;
            }
        }
    }



}

