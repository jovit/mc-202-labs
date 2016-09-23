#ifndef MARIOSHKA_LIST_H
#define MARIOSHKA_LIST_H
#include "Matrioshka.h"

typedef struct ListNode {
    struct ListNode *next;
    struct ListNode *previous;
    Matrioshka *matrioshka;
} ListNode;

typedef struct {
    ListNode *first;
} MatrioshkaList;

MatrioshkaList *new_list(); // allocates a new list
void free_list(MatrioshkaList *list); // deletes all matrioshkas from list
char add_to_list(MatrioshkaList *list, Matrioshka *matrioshka);

#endif
