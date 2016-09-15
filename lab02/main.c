#include "IntList.h"
#include <stdio.h>

#define ACCESS_OPERATION 'a'
#define REMOVE_OPERATION 'r'
#define INSERT_OPERATION 'i'


enum operation_type {
    MOVE_TO_FRONT,
    TRANSPOSE
};

int perform_operation(char operation, int value, IntList *list, enum operation_type type) {
    switch (operation) {
        case ACCESS_OPERATION:
            if (type == MOVE_TO_FRONT) {
                return mtf_access(list, value);
            } else {
                return tr_access(list, value);
            }
        case REMOVE_OPERATION:
            return remove_with_cost(list, value);
        case INSERT_OPERATION:
            if (type == MOVE_TO_FRONT) {
                return mtf_add(list, value);
            } else {
                return tr_add(list, value);
            }
        default:
            return 0;
    }
}

//prints all elements from the list
void print_list(IntList *list) {
    Node *current_node;

    if (list->first != NULL) {
        // goes through the whole list and prints the elements
        for (current_node = list->first; current_node->next != NULL; current_node = current_node->next) {
            printf("%d ", current_node->value);
        }

        printf("%d ", current_node->value);
    }

    printf("\n");
}

int main(void) {
    int mtf_cost = 0, tr_cost = 0;
    int number_of_values, number_of_requisitions, value;
    int i;
    char operation;
    IntList *mtf_list;
    IntList *tr_list;

    mtf_list = create_list();
    tr_list = create_list();

    scanf("%d %d", &number_of_values, &number_of_requisitions);

    for (i = 0; i < number_of_values; i++) {
        scanf("%d", &value);
        add_to_list(mtf_list, value);
        add_to_list(tr_list, value);
    }


    for (i = 0; i < number_of_requisitions; i++) {
        scanf(" %c %d", &operation, &value);
        mtf_cost += perform_operation(operation, value, mtf_list, MOVE_TO_FRONT);
        tr_cost += perform_operation(operation, value, tr_list, TRANSPOSE);
    }

    printf("%d\n", mtf_cost);
    print_list(mtf_list);

    printf("%d\n", tr_cost);
    print_list(tr_list);


    free_list(mtf_list);
    free_list(tr_list);

    return 0;
}