#ifndef SPLAYTREE_H
#define SPLAYTREE_H

#include "Queue.h"

typedef struct SplayTreeNode {
    char ingredient_name[INGREDIENT_NAME_MAX_SIZE];
    IngredientsQueue *ingredients_queue;
    struct SplayTreeNode *left, *right;
    int pizzas_waiting;
} SplayTreeNode;

typedef struct {
    SplayTreeNode *root;
} SplayTree;

SplayTree *create_splay_tree();
SplayTreeNode *search(SplayTree *tree, char *ingredient_name);
void insert(SplayTree *tree, char *ingredient_name);
char can_use_ingredient(SplayTree *tree, char *ingredient_name, int time);
void use_ingredient(SplayTree *tree, char *ingredient_name, int time);

#endif
