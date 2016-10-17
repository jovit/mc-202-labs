#ifndef QUEUE_H
#define QUEUE_H

#include "Ingredient.h"

typedef struct QueueNode {
    Ingredient *ingredient;
    struct QueueNode *next;
} QueueNode;

typedef struct {
    QueueNode *root;
} IngredientsQueue;

IngredientsQueue *create_queue();
void insert_to_queue(IngredientsQueue *queue, Ingredient *ingredient);
char is_queue_empty(IngredientsQueue *queue);
Ingredient *remove_from_queue(IngredientsQueue *queue);
Ingredient *peek_queue(IngredientsQueue *queue);
void free_queue(IngredientsQueue *queue);

#endif
