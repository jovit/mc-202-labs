#ifndef STACK_H
#define STACK_H
#include "Matrioshka.h"

typedef struct StackNode {
    Matrioshka *matrioshka;
    struct StackNode *next;
} StackNode;

typedef struct {
    StackNode *top;
} MatrioshkaStack;

MatrioshkaStack *new_stack();

void push(MatrioshkaStack *stack, Matrioshka *matrioshka);

Matrioshka *pop(MatrioshkaStack *stack);

Matrioshka *peek(MatrioshkaStack *stack);

char is_empty(MatrioshkaStack *stack);

void free_stack(MatrioshkaStack *stack);

#endif
