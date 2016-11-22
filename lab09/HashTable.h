#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "IntList.h"
#include "TreeAVL.h"

typedef struct HashTableValue {
    TreeAVL *pixels;
    int color;
    struct HashTableValue *next;
} HashTableValue;

typedef struct {
    long size;
    HashTableValue **values;
} HashTable;

HashTable *create_hash_table(long size);
void add_to_hash_table(HashTable *table, int color, unsigned long *another_pixel_key, unsigned long key);
void free_hash_table(HashTable *table);

#endif
