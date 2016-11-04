#ifndef QUEUE_H
#define QUEUE_H

typedef struct QueueNode {
    struct QueueNode *next;
    int value;
} QueueNode;

typedef struct {
    QueueNode *first;
    QueueNode *last;
} Queue;

void queue(Queue *queue, int value);
int dequeue(Queue *queue);
char is_queue_empty(Queue *queue);
Queue *create_queue();
void free_queue(Queue *queue);


#endif
