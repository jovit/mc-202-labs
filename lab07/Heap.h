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

HeapNode remove_max(Heap *heap);
Heap *create_heap(int capacity);
void set_priority(Heap *heap, int value, int new_key);
void insert(Heap *heap, HeapNode value);
void free_heap(Heap *heap);
