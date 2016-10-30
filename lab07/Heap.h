#ifndef HEAP_H
#define HEAP_H
typedef struct {
    int key;
    int value;
} HeapNode;
typedef struct {
    HeapNode *nodes;
    int size;
} Heap;
#endif

Heap *create_empty_heap(int size);
Heap *create_heap_from_array();
