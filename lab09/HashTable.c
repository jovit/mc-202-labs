#include <stddef.h>
#include <stdlib.h>
#include "HashTable.h"
#include "Utils.h"

HashTableValue *create_hash_table_value(int color) {
    HashTableValue *value = malloc(sizeof(HashTableValue));

    value->pixels = create_tree();
    value->color = color;
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
                free_tree(table->values[i]->pixels);
                table->values[i] = current->next;
                free(current);
                current = table->values[i];
            }

        }
    }

    free(table->values);
    free(table);
}
//falta padrão, muito complicado
void add_to_hash_table(HashTable *table, int color, unsigned long *another_pixel_key, unsigned long key) {
    HashTableValue *current_value;
    unsigned long index = (unsigned long) color % table->size;

    if (!table->values[index]) { // if there's no existing key in index
        table->values[index] = create_hash_table_value(color);
        insert_to_tree(table->values[index]->pixels, key);
    } else if (another_pixel_key) {
        current_value = table->values[index];

        while (current_value != NULL && !contains(current_value->pixels, *another_pixel_key)) { // looks for the key in case of collision
            current_value = current_value->next;
        }

        if (current_value != NULL) {
            insert_to_tree(current_value->pixels, key);
        } else {
            current_value = create_hash_table_value(color);
            current_value->next = table->values[index];
            table->values[index] = current_value->next;

            insert_to_tree(current_value->pixels, key);
        }
    } else {
        current_value = create_hash_table_value(color);
        current_value->next = table->values[index];
        table->values[index] = current_value->next;

        insert_to_tree(current_value->pixels, key);
    }


}

char contains_pixel(HashTable *table, int color, unsigned long key) {
    HashTableValue *current_value;
    unsigned long index = (unsigned long) color % table->size;

    current_value = table->values[index];
    if (current_value) {
        while (current_value != NULL &&
               !contains(current_value->pixels, key)) {
            current_value = current_value->next;
        }

        return current_value != NULL;
    } else {
        return 0;
    }
}
