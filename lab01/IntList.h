#ifndef LIST_H
#define LIST_H

typedef struct Node {
    struct Node* next;
    int value;
} Node;

typedef struct List {
    Node* first;
} IntList;

IntList* create_list();
void free_list(IntList* list);
void add_to_list(IntList* list, int value);

#endif
