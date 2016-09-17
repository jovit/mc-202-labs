#ifndef STACK_H
#define STACK_H

typedef struct StackNode {
    int value;
    struct StackNode *next;
} StackNode;

typedef struct Stack {
    StackNode *top;
} Stack;

Stack *new_stack();

void push(Stack *stack, int value);

int pop(Stack *stack);

int peek(Stack *stack);

char is_empty(Stack *stack);

void free_stack(Stack *stack);

#endif
