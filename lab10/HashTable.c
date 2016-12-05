#include <stddef.h>
#include <stdlib.h>
#include "HashTable.h"
#include "Utils.h"

HashTableValue *create_hash_table_value(unsigned long key) {
    HashTableValue *value = malloc(sizeof(HashTableValue));

    value->indexes = create_list();
    value->key = key;
    value->next = NULL;

    return value;
}

// initialize a empty hash table
HashTable *create_hash_table(long size) {
    HashTable *table = malloc(sizeof(HashTable));
    long i;
    validate_malloc(table);

    table->size = size;

    table->values = malloc(sizeof(HashTableValue*) * size);

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
                free_list(table->values[i]->indexes);
                table->values[i] = current->next;
                free(current);
                current = table->values[i];
            }

        }
    }

    free(table->values);
    free(table);
}

void add_to_hash_table(HashTable *table, unsigned long key) {
    HashTableValue *current_value;
    unsigned long index = key % table->size;

    if (!table->values[index]) { // if there's no existing key in index
        table->values[index] = create_hash_table_value(key);
    } else {
        current_value = table->values[index];

        while (current_value->next != NULL && current_value->key != key) { // looks for the key in case of collision
            current_value = current_value->next;
        }

        if (current_value->key != key) { // did not find the key
            current_value->next = create_hash_table_value(key);
        }
    }


}

// get the list of index of a word with matching key
IntList *get_key(HashTable *table, unsigned long key) {
    HashTableValue *current_value;
    unsigned long index = key % table->size;

    current_value = table->values[index];

    while (current_value->key != key) { // find the key
        current_value = current_value->next;
    }

    return current_value->indexes;
}

void add_connection(HashTable *table, unsigned long previous, unsigned long next) {

}
