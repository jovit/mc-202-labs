#ifndef MTF_INT_LIST_H
#define MTF_INT_LIST_H

typedef struct Node {
    struct Node *next;
    struct Node *previous;
    int value;
} Node;

typedef struct List {
    Node *first;
} IntList;

IntList *create_list(); // allocates a new list
void free_list(IntList *list);
void add_to_list(IntList *list, int value);
int remove_with_cost(IntList *list, int value);

int mtf_access(IntList *list, int value);
int mtf_add(IntList *list, int value);

int tr_access(IntList *list, int value);
int tr_add(IntList *list, int value);

#endif
