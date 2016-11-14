#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "IntList.h"

typedef struct {
    int size;
    IntList **values;
} HashTable;

HashTable *create_hash_table(int size);
void add_to_hash_table(HashTable *table, int value, long key);
void free_hash_table(HashTable *table);

#endif
