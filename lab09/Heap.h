#ifndef HEAP_H
#define HEAP_H
typedef struct {
    int key;
    int x;
    int y;
} HeapNode;
typedef struct {
    HeapNode *nodes;
    int size, capacity;
} Heap;
#endif

HeapNode remove_min(Heap *heap);
Heap *create_heap(int capacity);
void insert(Heap *heap, HeapNode value);
void free_heap(Heap *heap);
