#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "IntList.h"

typedef struct HashTableValue {
    IntList *indexes;
    long key;
    struct HashTableValue *next;
} HashTableValue;

typedef struct {
    long size;
    HashTableValue **values;
} HashTable;

HashTable *create_hash_table(long size);
void add_to_hash_table(HashTable *table, int value, unsigned long key);
IntList *get_key(HashTable *table, unsigned long key);
void free_hash_table(HashTable *table);

#endif
