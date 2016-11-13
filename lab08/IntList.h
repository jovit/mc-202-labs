#ifndef INTLIST_H
#define INTLIST_H
typedef struct IntListNode {
    int value;
    struct IntListNode *next;
} IntListNode;

typedef struct {
    IntListNode *root;
} IntList;

IntList *create_list();
void add_to_start(IntList *list, int value);
int get(IntList *list, int index);
void free_list(IntList *list);

#endif
