#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "LongList.h"

#define WORD_MAX_SIZE 51

typedef struct HashTableValue {
    LongList *connections;
    unsigned long key;
    char word[WORD_MAX_SIZE];
    char visited;
    int distance;
    unsigned long previous;
    struct HashTableValue *next;
} HashTableValue;

typedef struct {
    long size;
    HashTableValue **values;
} HashTable;

HashTable *create_hash_table(long size);
void add_connection(HashTable *table, unsigned long previous, unsigned long next);
void add_to_hash_table(HashTable *table, unsigned long key, char word[WORD_MAX_SIZE]);
void free_hash_table(HashTable *table);
void print_smallest_path(HashTable *table, unsigned long start, unsigned long finish, int weight);

#endif
