#include <stdlib.h>
#include <limits.h>
#include "Heap.h"
#include "Utils.h"

// get parent index of i
int parent(int i) {
    return (i-1)/2;
}

// get the left node index from i
int left(int i) {
    return (2*i) + 1;
}

// get the right node index from i
int right(int i) {
    return (2*i) + 2;
}


void free_heap(Heap *heap) {
    free(heap->nodes);
    free(heap);
}

// swap two values
void swap(HeapNode *x, HeapNode *y) {
    HeapNode aux = *x;
    *x = *y;
    *y = aux;
}

// insert to min heap
void insert(Heap *heap, HeapNode value) {
    int i;
    if (heap->size < heap->capacity) { // if heap not full
        heap->size++;
        i = heap->size - 1;
        heap->nodes[i] = value; // add value to the end of the array

        // bring element up to fix the heap
        while (i != 0 && heap->nodes[parent(i)].weight > heap->nodes[i].weight) {
            swap(&heap->nodes[i], &heap->nodes[parent(i)]);
            i = parent(i);
        }
    }
}

// get's a element down to fix a heap property
void heapfy(Heap *heap, int i) {
    int smallest = i;

    if (left(i) < heap->size && heap->nodes[left(i)].weight < heap->nodes[smallest].weight) {
        smallest = left(i);
    }

    if (right(i) < heap->size && heap->nodes[right(i)].weight < heap->nodes[smallest].weight) {
        smallest = right(i);
    }

    if (i != smallest) {
        swap(&heap->nodes[i], &heap->nodes[smallest]);
        heapfy(heap, smallest);
    }
}

// removes the root from the min heap and returns it
HeapNode remove_min(Heap *heap) {
    HeapNode min;
    if (heap->size > 0) {
        min = heap->nodes[0];
        heap->nodes[0] = heap->nodes[heap->size-1]; // replace root with the last element
        heap->size--;
        // fix heap properties
        heapfy(heap, 0);
    } else {
        min.key = 0;
        min.weight = 0;
    }

    return min;
}

// initializes a heap
Heap *create_heap(int capacity) {
    Heap *new_heap = malloc(sizeof(Heap));

    validate_malloc(new_heap);

    new_heap->capacity = capacity;
    new_heap->size = 0;
    new_heap->nodes = malloc(sizeof(HeapNode) * capacity);
    validate_malloc(new_heap->nodes);

    return new_heap;
}

HeapNode peek_heap(Heap *heap) {
    HeapNode min;
    if (heap->size > 0) {
        min = heap->nodes[0];
    } else {
        min.key = 0;
        min.weight = INT_MAX;
    }

    return min;
}


