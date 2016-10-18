#ifndef INGREDIET_LIST_H
#define INGREDIET_LIST_H

#include "Ingredient.h"

typedef struct IngredientListNode {
    struct IngredientListNode *next;
    Ingredient *value;
} IngredientListNode;

typedef struct IngredientList {
    IngredientListNode *first;
} IngredientList;

IngredientList* create_ingredient_list(); // allocates a new list
void free_ingredient_list(IngredientList *list);
void add_to_ingredient_list(IngredientList *list, Ingredient *value);

#endif
