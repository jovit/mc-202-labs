#ifndef HEAP_H
#define HEAP_H
typedef struct {
    int key;
    int value;
} HeapNode;
typedef struct {
    HeapNode *nodes;
    int size, capacity;
} Heap;
#endif

Heap *create_empty_heap(int capacity);
void free_heap(Heap *heap);
