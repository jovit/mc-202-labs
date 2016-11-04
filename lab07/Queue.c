#include <stdlib.h>
#include "Queue.h"
#include "Utils.h"

Queue *create_queue() { // initializes a new queue
    Queue *new_queue = malloc(sizeof(Queue));
    validate_malloc(new_queue);

    new_queue->first = NULL;
    new_queue->last = NULL;

    return new_queue;
}

void free_queue(Queue *queue) { // frees all nodes from a queue
    QueueNode *current_node, *node_to_delete;

    current_node = queue->first;
    while (current_node != NULL) {
        node_to_delete = current_node;
        current_node = current_node->next;

        free(node_to_delete);
    }

    free(queue);
}

// removes the first node from the queue and returns its value
int dequeue(Queue *queue) {
    int return_value;
    QueueNode *value_to_delete;

    value_to_delete = queue->first;
    return_value = value_to_delete->value;
    queue->first = value_to_delete->next;

    free(value_to_delete);

    return return_value;
}

// check if the queue is empty
char is_queue_empty(Queue *queue) {
    return queue->first == NULL;
}

// add element to the end of the queue
void queue(Queue *queue, int value) {
    QueueNode *new_node = malloc(sizeof(QueueNode));
    validate_malloc(new_node);

    new_node->next = NULL;
    new_node->value = value;

    if (queue->first == NULL) {
        queue->first = new_node;
        queue->last = new_node;
    } else {
        queue->last->next = new_node;
        queue->last = new_node;
    }
}


