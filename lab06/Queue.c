#include <stdlib.h>
#include "Queue.h"
#include "Utils.h"

IngredientsQueue *create_queue() {
    IngredientsQueue *new_queue = malloc(sizeof(IngredientsQueue));

    validate_malloc(new_queue);

    new_queue->root = NULL;

    return new_queue;
}

char is_queue_empty(IngredientsQueue *queue) {
    return queue->root == NULL;
}

QueueNode *new_queue_node(Ingredient *ingredient) {
    QueueNode *new_queue_node = malloc(sizeof(QueueNode));

    validate_malloc(new_queue_node);

    new_queue_node->ingredient = ingredient;
    new_queue_node->next = NULL;

    return new_queue_node;
}

void insert_to_queue(IngredientsQueue *queue, Ingredient *ingredient) {
    QueueNode *new_node = new_queue_node(ingredient);
    QueueNode *current;

    if (queue->root == NULL) {
        queue->root = new_node;
    } else {
        current = queue->root;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

Ingredient *remove_from_queue(IngredientsQueue *queue) {
    Ingredient *result = NULL;
    QueueNode *removed;
    if (!is_queue_empty(queue)) {
        result = queue->root->ingredient;
        removed = queue->root;
        queue->root = queue->root->next;

        free(removed);
    }
    return result;
}

void free_queue(IngredientsQueue *queue) {
    QueueNode *current;
    while (!is_queue_empty(queue)) {
        current = queue->root;
        queue->root = queue->root->next;

        free(current->ingredient);
        free(current);
    }

}

Ingredient *peek_queue(IngredientsQueue *queue) {
    return queue->root;
}
