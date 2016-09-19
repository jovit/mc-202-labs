#ifndef STACK_H
#define STACK_H
#include "Matrioshka.h"

typedef struct StackNode {
    Matrioshka *value;
    struct StackNode *next;
} StackNode;

typedef struct MatrioshkaStack {
    StackNode *top;
} Stack;

Stack *new_stack();

void push(MatrioshkaStack *stack, Matrioshka *value);

Matrioshka *pop(MatrioshkaStack *stack);

Matrioshka *peek(MatrioshkaStack *stack);

char is_empty(MatrioshkaStack *stack);

void free_stack(MatrioshkaStack *stack);

#endif
