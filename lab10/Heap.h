#ifndef HEAP_H
#define HEAP_H
typedef struct {
    int weight;
    unsigned long key;
} HeapNode;
typedef struct {
    HeapNode *nodes;
    int size, capacity;
} Heap;
#endif

HeapNode remove_min(Heap *heap);
HeapNode peek_heap(Heap *heap);
Heap *create_heap(int capacity);
void insert(Heap *heap, HeapNode value);
void free_heap(Heap *heap);
