#include <stdlib.h>
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

// insert to max heap
void insert(Heap *heap, HeapNode value) {
    int i;
    if (heap->size < heap->capacity) { // if heap not full
        heap->size++;
        i = heap->size - 1;
        heap->nodes[i] = value; // add value to the end of the array

        // bring element up to fix the heap
        while (i != 0 && heap->nodes[parent(i)].key < heap->nodes[i].key) {
            swap(&heap->nodes[i], &heap->nodes[parent(i)]);
            i = parent(i);
        }
    }
}

// get's a element down to fix a heap property
void heapfy(Heap *heap, int i) {
    int biggest = i;

    if (left(i) < heap->size && heap->nodes[left(i)].key > heap->nodes[biggest].key) {
        biggest = left(i);
    }
    if (right(i) < heap->size && heap->nodes[right(i)].key > heap->nodes[biggest].key) {
        biggest = right(i);
    }
    if (i != biggest) {
        swap(&heap->nodes[i], &heap->nodes[biggest]);
        heapfy(heap, biggest);
    }
}

// removes the root from the max heap and returns it
HeapNode remove_max(Heap *heap) {
    HeapNode max = heap->nodes[0];
    heap->nodes[0] = heap->nodes[heap->size-1]; // replace root with the last element
    heap->size--;
    // fix heap properties
    heapfy(heap, 0);

    return max;
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

// increases the priority from the node on i
void increase_priority(Heap *heap, int i, int new_key) {
    heap->nodes[i].key = new_key;

    // bring the element up if the heap properties have been broken
    while (i != 0 && heap->nodes[parent(i)].key < heap->nodes[i].key) {
        swap(&heap->nodes[i], &heap->nodes[parent(i)]);
        i = parent(i);
    }
}

// decreases the priority from the element on i
void decrease_priority(Heap *heap, int i, int new_key) {
    heap->nodes[i].key = new_key;
    heapfy(heap, i); // bring the element down if the heap properties have been broken
}

// sets the priority of a node by value
void set_priority(Heap *heap, int value, int new_key) {
    int i = 0;

    for (i = 0; i < heap->size; i++) { // find the node on the heap
        if (heap->nodes[i].value == value) {
            // increase or decrease the priority given the key
            if (heap->nodes[i].key < new_key) {
                increase_priority(heap, i, new_key);
            } else {
                decrease_priority(heap, i, new_key);
            }
            break;
        }
    }
}

