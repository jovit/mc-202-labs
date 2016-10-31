#include <stdlib.h>
#include "Heap.h"
#include "Utils.h"

//http://quiz.geeksforgeeks.org/binary-heap/

int parent(int i) {
    return (i-1)/2;
}

int left(int i) {
    return (2*i) + 1;
}

int right(int i) {
    return (2*i) + 2;
}

Heap *create_empty_heap(int capacity) {
    Heap *result = malloc(sizeof(Heap));
    validate_malloc(result);

    result->size = 0;
    result->capacity = capacity;
    result->nodes = malloc(sizeof(HeapNode) * capacity);

    validate_malloc(result->nodes);

    return result;
}

void free_heap(Heap *heap) {
    free(heap->nodes);
    free(heap);
}
