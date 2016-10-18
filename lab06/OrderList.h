#ifndef ORDERLIST_H
#define ORDERLIST_H


#include "IngredientList.h"

typedef struct OrderListNode {
    struct OrderListNode *next;
    int order;
    IngredientList *ingredients;
} OrderListNode;

typedef struct OrderList {
    OrderListNode *first;
} OrderList;

OrderList* create_order_list(); // allocates a new list
void free_order_list(OrderList *list);
void add_to_order_list(OrderList *list, int order, IngredientList *ingredientList);
void remove_order(OrderList *list, int order);

#endif
