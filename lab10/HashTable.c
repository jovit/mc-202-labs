#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "HashTable.h"
#include "Utils.h"
#include "Heap.h"

HashTableValue *create_hash_table_value(unsigned long key, char word[WORD_MAX_SIZE]) {
    HashTableValue *value = malloc(sizeof(HashTableValue));

    value->connections = create_list();
    value->key = key;
    value->next = NULL;
    value->visited = 0;
    strcpy(value->word, word);

    return value;
}

// initialize a empty hash table
HashTable *create_hash_table(long size) {
    HashTable *table = malloc(sizeof(HashTable));
    long i;
    validate_malloc(table);

    table->size = size;

    table->values = malloc(sizeof(HashTableValue *) * size);

    for (i = 0; i < size; i++) {
        table->values[i] = NULL;
    }

    return table;
}


void free_hash_table(HashTable *table) {
    int i;
    HashTableValue *current;

    // free all nodes from table
    for (i = 0; i < table->size; i++) {
        if (table->values[i]) { // free the list
            current = table->values[i];

            while (current) {
                free_list(table->values[i]->connections);
                table->values[i] = current->next;
                free(current);
                current = table->values[i];
            }

        }
    }

    free(table->values);
    free(table);
}

void add_to_hash_table(HashTable *table, unsigned long key, char word[WORD_MAX_SIZE]) {
    HashTableValue *current_value;
    unsigned long index = key % table->size;

    if (!table->values[index]) { // if there's no existing key in index
        table->values[index] = create_hash_table_value(key, word);
    } else {
        current_value = table->values[index];

        while (current_value->next != NULL && current_value->key != key) { // looks for the key in case of collision
            current_value = current_value->next;
        }

        if (current_value->key != key) { // did not find the key
            current_value->next = create_hash_table_value(key, word);
        }
    }
}

void add_connection(HashTable *table, unsigned long previous, unsigned long next) {
    HashTableValue *current_value;
    unsigned long index = previous % table->size;

    current_value = table->values[index];

    while (current_value->next != NULL && current_value->key != previous) { // looks for the key in case of collision
        current_value = current_value->next;
    }

    add_to_start(current_value->connections, next);

}

void print_word_by_key(HashTable *table, unsigned long key) {
    HashTableValue *current_value;
    unsigned long index = key % table->size;

    current_value = table->values[index];

    while (current_value->next != NULL && current_value->key != key) { // looks for the key in case of collision
        current_value = current_value->next;
    }

    printf("%s", current_value->word);
}

LongList *get_connections(HashTable *table, unsigned long key) {
    HashTableValue *current_value;
    unsigned long index = key % table->size;

    current_value = table->values[index];

    while (current_value->next != NULL && current_value->key != key) { // looks for the key in case of collision
        current_value = current_value->next;
    }

    return current_value->connections;
}

HashTableValue *get_value(HashTable *table, unsigned long key) {
    HashTableValue *current_value;
    unsigned long index = key % table->size;

    current_value = table->values[index];

    while (current_value->next != NULL && current_value->key != key) { // looks for the key in case of collision
        current_value = current_value->next;
    }

    return current_value;
}

void print_words_by_keys(HashTable *table, unsigned long *path) {
    int i;

    for (i = 0; path[i]; i++) { // while path[i] != 0
        print_word_by_key(table, path[i]);
        if (path[i+1]) {
            printf(" ");
        }
    }
}

void print_smallest_path(HashTable *table, unsigned long start, unsigned long finish, int weight) {
    int i;
    int path_size;
    char found = 0;
    HashTableValue *current_vertex, *next_vertex;
    LongListNode *connection;
    LongList *connections;
    unsigned long *path;
    Heap *heap;
    HeapNode heap_node;

    path = malloc(sizeof(unsigned long) * (table->size+1));
    validate_malloc(path);

    for (i = 0; i < table->size; i++) { // initialize all vertexes for the dijkstra algorithm
        if (table->values[i]){
            current_vertex = table->values[i];
            while (current_vertex != NULL) {
                current_vertex->visited = 0;
                current_vertex->previous = 0;
                current_vertex->distance = INT_MAX;
                current_vertex = current_vertex->next;
            }
        }
    }

    current_vertex = get_value(table, start); // get the starting vertex
    current_vertex->distance = 0; // distance to the start is always 0

    heap = create_heap((int) table->size);
    heap_node.key = start;
    heap_node.weight = 0;
    insert(heap, heap_node); // insert the initial vertex to the priority queue

    while (heap->size > 0) {
        heap_node = remove_min(heap); // get the vertex with smallest distance

        if (heap_node.key == finish) { // if has found the end
            found = 1;
            break;
        }

        connections = get_connections(table, heap_node.key); // get the connections the the current vertex
        current_vertex = get_value(table, heap_node.key);
        current_vertex->visited = 1; // mark current vertex as visited

        for (connection = connections->root; connection; connection = connection->next) { // for each connection
            next_vertex = get_value(table, connection->value);

            // if current connection wasn't visited and has a smaller distance than it's previous distance
            if (!next_vertex->visited &&
                    (current_vertex->distance + (weight - connection->count)) <= next_vertex->distance) {
                // ads the vertex to the priority queue and updates its parent value and distance
                next_vertex->previous = current_vertex->key;
                next_vertex->distance = current_vertex->distance + (weight - connection->count);
                heap_node.key = next_vertex->key;
                heap_node.weight = next_vertex->distance;

                insert(heap, heap_node);
            }
        }
    }

    if (!found) {
        printf("erro");
    } else { // if did find a path
        current_vertex = get_value(table, finish); // get the finish vertex

        // go through the path backwards to find the size of the path
        for (path_size = 0; current_vertex->distance > 0; current_vertex = get_value(table, current_vertex->previous)) {
            path_size++;
        }

        path[path_size+1] = 0; // set ending point to the path array
        // fill the path array with the keys from the vertexes
        for (current_vertex = get_value(table, finish); path_size >= 0; path_size--) {
            path[path_size] = current_vertex->key;
            if (path_size > 0) {
                current_vertex = get_value(table, current_vertex->previous);
            }
        }

        print_words_by_keys(table, path); // print all words by the keys on the path array
    }

    free(path);
    free_heap(heap);
}