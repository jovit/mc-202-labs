#include <stdlib.h>
#include <stdio.h>
#include "Stack.h"

// validate if the malloc has not failed
void validate_malloc(void *pointer) {
    if (pointer == NULL) {
        printf("Out of memory");
        exit(1);
    }
}

void push(MatrioshkaStack *stack, Matrioshka *value) {
    StackNode *new_node = malloc(sizeof(StackNode));

    validate_malloc(new_node);

    new_node->value = value;

    new_node->next = stack->top;
    stack->top = new_node;

}

Matrioshka *pop(MatrioshkaStack *stack) {
    Matrioshka *value;
    StackNode *next_node;

    if (!is_empty(stack)) {
        value = stack->top->value;
        next_node = stack->top->next;
        free(stack->top);
        stack->top = next_node;
    } else {
        value = NULL;
    }

    return value;
}

char is_empty(MatrioshkaStack *stack) {
    return stack->top == NULL;
}

MatrioshkaStack *new_stack() {
    MatrioshkaStack *new_stack = malloc(sizeof(MatrioshkaStack));
    validate_malloc(new_stack);
    new_stack->top = NULL;
    return new_stack;
}

Matrioshka *peek(MatrioshkaStack *stack) {
    Matrioshka *value;

    if (!is_empty(stack)) {
        value = stack->top->value;
    } else {
        value = NULL;
    }

    return value;
}

void free_stack(Stack *stack) {
    while(!is_empty(stack)) {
        free(pop(stack));
    }

    free(stack);
}
