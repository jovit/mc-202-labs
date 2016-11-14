#include <stddef.h>
#include <stdlib.h>
#include "HashTable.h"
#include "Utils.h"

HashTable *create_hash_table(int size) {
    HashTable *table = malloc(sizeof(HashTable));
    int i;
    validate_malloc(table);

    table->size = size;

    table->values = malloc(sizeof(IntList*) * size);

    for (i = 0; i < size; i++) {
        table->values[i] = create_list();
    }


    return table;
}



void free_hash_table(HashTable *table) {
    int i;

    for (i = 0; i < table->size; i++) {
        if (table->values[i]) {
            free(table->values[i]);
        }
    }

    free(table->values);
    free(table);
}

void add_to_hash_table(HashTable *table, int value, long key) {
    int index = (int) (key % table->size);

    if (!table->values[index]) {
        table->values[index] = create_list();
    }

    add_to_start(table->values[index], value);
}
