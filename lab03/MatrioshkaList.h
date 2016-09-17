#ifndef MARIOSHKA_LIST_H
#define MARIOSHKA_LIST_H

typedef struct {
    int value;
    int n;
} Matrioshka;

typedef struct ListNode {
    struct ListNode *next;
    struct ListNode *previous;
    Matrioshka value;
} ListNode;

typedef struct {
    ListNode *first;
} MatrioshkaList;

MatrioshkaList *create_list(); // allocates a new list
void free_list(MatrioshkaList *list);
void add_to_list(MatrioshkaList *list, int value);



#endif
