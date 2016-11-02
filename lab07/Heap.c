#include <stdlib.h>
#include "Heap.h"
#include "Utils.h"

int parent(int i) {
    return (i-1)/2;
}

int left(int i) {
    return (2*i) + 1;
}

int right(int i) {
    return (2*i) + 2;
}


void free_heap(Heap *heap) {
    free(heap->nodes);
    free(heap);
}

void swap(HeapNode *x, HeapNode *y) {
    HeapNode aux = *x;
    *x = *y;
    *y = aux;
}

void insert(Heap *heap, HeapNode value) {
    int i;
    if (heap->size < heap->capacity) {
        heap->size++;
        i = heap->size - 1;
        heap->nodes[i] = value;

        while (i != 0 && heap->nodes[parent(i)].key < heap->nodes[i].key) {
            swap(&heap->nodes[i], &heap->nodes[parent(i)]);
            i = parent(i);
        }
    }
}

void heapfy(Heap *heap, int i) {
    int biggest = i;
    if (left(i) < heap->size && heap->nodes[left(i)].key > heap->nodes[biggest].key)
        biggest = left(i);
    if (right(i) < heap->size && heap->nodes[right(i)].key > heap->nodes[biggest].key)
        biggest = right(i);
    if (i != biggest) {
        swap(&heap->nodes[i], &heap->nodes[biggest]);
        heapfy(heap, biggest);
    }
}

HeapNode increasePriority(Heap *heap, int i) {

}

HeapNode remove_max(Heap *heap) {
    HeapNode max = heap->nodes[0];
    heap->nodes[0] = heap->nodes[heap->size-1];
    heap->size--;
    heapfy(heap, 0);

    return max;
}

Heap *create_heap_from_array(int capacity, HeapNode *nodes) {
    int i;
    Heap *new_heap = malloc(sizeof(Heap));

    validate_malloc(new_heap);

    new_heap->capacity = capacity;
    new_heap->nodes = nodes;

    for (i = parent(new_heap->capacity - 1); i >= 0; i--)
        heapfy(new_heap, i);

    return new_heap;
}

Heap *create_heap(int capacity) {
    Heap *new_heap = malloc(sizeof(Heap));

    validate_malloc(new_heap);

    new_heap->capacity = capacity;
    new_heap->size = 0;
    new_heap->nodes = malloc(sizeof(HeapNode) * capacity);
    validate_malloc(new_heap->nodes);

    return new_heap;
}

char is_empty(Heap *heap) {
    return heap->size == 0;
}

void increase_priority(Heap *heap, int i, int new_key) {
    heap->nodes[i].key = new_key;

    while (i != 0 && heap->nodes[parent(i)].key < heap->nodes[i].key) {
        swap(&heap->nodes[i], &heap->nodes[parent(i)]);
        i = parent(i);
    }
}

void decrease_priority(Heap *heap, int i, int new_key) {
    heap->nodes[i].key = new_key;
    heapfy(heap, i);
}

void set_priority(Heap *heap, int value, int new_key) {
    int i = 0;

    for (i = 0; i < heap->size; i++) {
        if (heap->nodes[i].value == value) {
            if (heap->nodes[i].key < new_key) {
                increase_priority(heap, i, new_key);
            } else {
                decrease_priority(heap, i, new_key);
            }
            break;
        }
    }
}

int get_max(Heap *heap) {
    return heap->nodes[0].value;
}
