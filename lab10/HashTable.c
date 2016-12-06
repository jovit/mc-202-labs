#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "HashTable.h"
#include "Utils.h"
#include "Heap.h"
#include "LongList.h"
#include "TreeAVL.h"

HashTableValue *create_hash_table_value(unsigned long key, char word[WORD_MAX_SIZE]) {
    HashTableValue *value = malloc(sizeof(HashTableValue));

    value->connections = create_list();
    value->key = key;
    value->next = NULL;
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

LongList *get_connections(HashTable *table, unsigned long key) {
    HashTableValue *current_value;
    unsigned long index = key % table->size;

    current_value = table->values[index];

    while (current_value->next != NULL && current_value->key != key) { // looks for the key in case of collision
        current_value = current_value->next;
    }

    return current_value->connections;
}

void print_smallest_path(HashTable *table, unsigned long start, unsigned long finish, int weight) {
    HashTableValue *current_value;
    Heap *heap;
    HeapNode heap_node;
    LongList *connections;
    LongListNode *current_list_node;
    TreeAVL *passed_nodes;
    int previous_weight;
    unsigned long index = start % table->size;

    heap = create_heap((int) table->size);
    passed_nodes = create_tree();

    connections = get_connections(table, start);

    for (current_list_node = connections->root; current_list_node != NULL; current_list_node = current_list_node->next) {
        heap_node.key = current_list_node->value;
        heap_node.weight = 0;

        insert_to_tree(passed_nodes, current_list_node->value);
        insert(heap, heap_node);
    }

    while (1) {
        heap_node = remove_min(heap);

        if (heap_node.key == 0 && heap_node.weight == 0) {
            printf("erro");
            break;
        }

        if (heap_node.key == finish) {
            printf("%d", heap_node.weight);
        }

        previous_weight = heap_node.weight;

        connections = get_connections(table, heap_node.key);
        for (current_list_node = connections->root; current_list_node != NULL; current_list_node = current_list_node->next) {
            if (get_count(passed_nodes, current_list_node->value) == 0) {
                heap_node.key = current_list_node->value;
                heap_node.weight = weight - current_list_node->count + previous_weight;

                insert_to_tree(passed_nodes, current_list_node->value);
                insert(heap, heap_node);
            }
        }
    }

    free_heap(heap);
    free_tree(passed_nodes);
}
