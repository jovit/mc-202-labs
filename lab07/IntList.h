#ifndef LIST_H
#define LIST_H

typedef struct Node {
    struct Node *next;
    int value;
} Node;

typedef struct {
    Node *first;
} IntList;

IntList* create_list(); // allocates a new list
void free_list(IntList* list);
void add_to_list(IntList* list, int value);
char list_contains(IntList* list, int key);
void remove_from_list(IntList* list, int key);

#endif
