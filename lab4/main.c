
#include <stdio.h>
#include <stdlib.h>
#include "MallocUtils.h"
#include "MatrioshkaStack.h"
#include "MatrioshkaList.h"

#define ERROR_MESSAGE "sequencia invalida ou nao pode colorir"
#define SUCCESS_MESSAGE "sequencia valida pode ser colorida"

void print_matrioshka_list(MatrioshkaList *matrioshka_list) {
    ListNode *current = matrioshka_list->first;
    while (current != NULL) {
        if (current->matrioshka->color == BLUE) {
            printf("\n%d: azul", current->matrioshka->value);
        } else {
            printf("\n%d: vermelho", current->matrioshka->value);
        }

        current = current->next;
    }

}

int main(void) {
    int size, i, value, sum;
    char invalid_matrioshka = 0;
    MatrioshkaStack *matrioshka_stack = new_stack();
    MatrioshkaList *matrioshka_list = new_list();
    Matrioshka *new_matrioshka, *top_matrioshka;

    scanf("%d", &size);

    for (i = 0; i < size; i++) {
        scanf("%d", &value);
        if (value < 0) { // if its the opening of a mtrioshka
            new_matrioshka = malloc(sizeof(Matrioshka));
            validate_malloc(new_matrioshka);
            new_matrioshka->value = -value;
            new_matrioshka->blue_child = 0;

            push(matrioshka_stack, new_matrioshka); // add new matrioshka to the stack
        } else { // if its closing a matrioshka
            if (peek(matrioshka_stack)->value != value) { // closing the wrong matrioshka
                printf(ERROR_MESSAGE);
                invalid_matrioshka = 1;
                break;
            } else {
                top_matrioshka = pop(matrioshka_stack); // get the matrioshka being closed
                sum = top_matrioshka->value + top_matrioshka->blue_child; // sum to check if its blue or red

                if (sum % 2 == 0) {
                    top_matrioshka->color = BLUE;
                    if (!is_empty(matrioshka_stack)) { // if its blue, add to the parent blue children count
                        peek(matrioshka_stack)->blue_child += 1;
                    }
                } else {
                    top_matrioshka->color = RED;
                }

                // if already have the same matrioshka with other color
                if (!add_to_list(matrioshka_list, top_matrioshka)) {
                    free(top_matrioshka);
                    printf(ERROR_MESSAGE);
                    invalid_matrioshka = 1;
                    break;
                }
            }

            if (is_empty(matrioshka_stack) && i < size-1) { // if there's more than one matrioshka with no parent
                printf(ERROR_MESSAGE);
                invalid_matrioshka = 1;
                break;
            }

        }
    }

    if (!invalid_matrioshka ) { // if the list of matrioshkas was valid
        printf(SUCCESS_MESSAGE);
        print_matrioshka_list(matrioshka_list);
    }

    free_list(matrioshka_list);
    free_stack(matrioshka_stack);

    return 0;
}