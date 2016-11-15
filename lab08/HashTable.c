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

    for (i = 0; i < table->size; i++) {
        if (table->values[i]) {
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

void add_to_hash_table(HashTable *table, int value, unsigned long key) {
    HashTableValue *current_value;
    unsigned long index = key % table->size;

    if (!table->values[index]) {
        table->values[index] = create_hash_table_value(key);
        add_to_start(table->values[index]->indexes, value);
    } else {
        current_value = table->values[index];

        while (current_value->next != NULL && current_value->key != key) {
            current_value = current_value->next;
        }

        if (current_value->key != key) {
            current_value->next = create_hash_table_value(key);
            current_value = current_value->next;
        }

        add_to_start(current_value->indexes, value);
    }


}

IntList *get_key(HashTable *table, unsigned long key) {
    HashTableValue *current_value;
    unsigned long index = key % table->size;

    current_value = table->values[index];

    while (current_value->key != key) {
        current_value = current_value->next;
    }

    return current_value->indexes;
}
