#include <stdlib.h>
#include <stdio.h>
#include "MallocUtils.h"
#include "MatrioshkaStack.h"

void push(MatrioshkaStack *stack, Matrioshka *matrioshka) {
    StackNode *new_node = malloc(sizeof(StackNode));

    validate_malloc(new_node);

    new_node->matrioshka = matrioshka;

    new_node->next = stack->top;
    stack->top = new_node;

}

Matrioshka *pop(MatrioshkaStack *stack) {
    Matrioshka *value;
    StackNode *next_node;

    if (!is_empty(stack)) {
        value = stack->top->matrioshka;
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
        value = stack->top->matrioshka;
    } else {
        value = NULL;
    }

    return value;
}

void free_stack(MatrioshkaStack *stack) {
    while(!is_empty(stack)) {
        free(pop(stack));
    }
    free(stack);
}
