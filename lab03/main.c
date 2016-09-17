
#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"

int main(void) {
    int size, i, value;
    Stack *original_stack = new_stack();
    Stack *open_matrioshkas = new_stack();

    scanf("%d", &size);

    for (i = 0; i < size; i++) {
        scanf("%d", &value);
        push(original_stack, value);
    }

    while (!is_empty(original_stack)) {
        value = pop(original_stack);

        if (value < 0) {
            push(open_matrioshkas, -value);
        } else {
            if (peek(open_matrioshkas) != value) {
                printf("sequencia invalida ou nao pode colorir\n");
                break;
            } else {
                pop(open_matrioshkas);
            }
        }
    }

    free(original_stack);
    free(open_matrioshkas);

    return 0;
}