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

Heap *create_heap_from_array(int capacity, HeapNode *nodes);
HeapNode remove_max(Heap *heap);
int get_max(Heap *heap);
Heap *create_heap(int capacity);
void set_priority(Heap *heap, int value, int new_key);
void insert(Heap *heap, HeapNode value);
char is_empty(Heap *heap);
void free_heap(Heap *heap);
