#include <stdio.h>
#include <stdlib.h>
#include "IntList.h"

// finds the value starting from the node start or returns NULL
Node *find_node(Node *start, int value) {
    Node *current_node = start;

    // while the list has not ended and the value wasn't found
    while (current_node != NULL && current_node->value != value) {
        current_node = current_node->next;
    }

    return current_node;
}

// gets the starting node for the first list
Node *get_first_list_start(IntList *original_list, int m) {
    Node *starting_node;
    starting_node = find_node(original_list->first, m);

    // if did not find m the first node is the first node from the original list
    if (starting_node == NULL) {
        starting_node = original_list->first;
    }

    return starting_node;
}

// gets the starting node for the second list
Node *get_second_list_start(IntList *original_list, int m, int n) {
    Node *starting_node, *first_list_start;
    first_list_start = get_first_list_start(original_list, m);

    starting_node = find_node(first_list_start, n);

    // if did not find n the first node is the first node from the first list
    if (starting_node == NULL) {
        starting_node = first_list_start;
    }


    return starting_node;
}

// gets the starting node for the third list
Node *get_third_list_start(IntList *original_list, int m, int n, int p) {
    Node *starting_node, *second_list_start;

    second_list_start = get_second_list_start(original_list, m, n);

    starting_node = find_node(second_list_start, p);

    // if did not find p the first node is the first node from the second list
    if (starting_node == NULL) {
        starting_node = second_list_start;
    }


    return starting_node;
}

// creates the first list
IntList *get_first_list(IntList *original_list, int m, int n, int p) {
    Node *starting_node, *ending_node, *current_node;
    IntList *first_list;

    first_list = create_list();

    starting_node = get_first_list_start(original_list, m);
    ending_node = find_node(starting_node, n);

    if (ending_node == NULL) {
        ending_node = find_node(starting_node, p);
    }

    current_node = starting_node;

    // replicates the original list from the starting to the end node
    while (current_node != ending_node) {
        add_to_list(first_list, current_node->value);
        current_node = current_node->next;
    }

    // if the ending node wasn't the end of the list
    if (current_node != NULL) {
        add_to_list(first_list, current_node->value);
    }

    return first_list;
}

// creates the second list
IntList *get_second_list(IntList *original_list, int m, int n, int p) {
    Node *starting_node, *ending_node, *current_node;
    IntList *second_list;

    second_list = create_list();

    starting_node = get_second_list_start(original_list, m, n);

    ending_node = find_node(starting_node, p);

    current_node = starting_node;

    // replicates the original list from the starting to the end node
    while (current_node != ending_node) {
        add_to_list(second_list, current_node->value);
        current_node = current_node->next;
    }

    // if the ending node wasn't the end of the list
    if (current_node != NULL) {
        add_to_list(second_list, current_node->value);
    }

    return second_list;
}

// creates the third list
IntList *get_third_list(IntList *original_list, int m, int n, int p) {
    Node *starting_node, *current_node;
    IntList *third_list;

    third_list = create_list();

    starting_node = get_third_list_start(original_list, m, n, p);

    current_node = starting_node;

    // replicates the original list from the starting node to the end of the list
    while (current_node != NULL) {
        add_to_list(third_list, current_node->value);
        current_node = current_node->next;
    }

    return third_list;
}

//prints all elements from the list
void print_list(IntList *list) {
    Node *current_node;

    // goes through the whole list and prints the elements
    for (current_node = list->first; current_node != NULL; current_node = current_node->next) {
        printf(" %d", current_node->value);
    }

    printf("\n");
}

int main(void) {
    int number_read, m, n, p;
    char char_read = ' ';
    IntList *original_list, *first_list, *second_list, *third_list;

    original_list = create_list();

    // while its not a new line ads the values read to the list
    while (char_read == ' ') {
        scanf("%d%c", &number_read, &char_read);
        add_to_list(original_list, number_read);
    }

    scanf("%d %d %d", &m, &n, &p);

    first_list = get_first_list(original_list, m, n, p);
    second_list = get_second_list(original_list, m, n, p);
    third_list = get_third_list(original_list, m, n, p);


    // print the original list
    printf("original");
    print_list(original_list);

    printf("m=%d, n=%d, p=%d\n", m, n, p);

    // print the first list
    printf("primeira");
    print_list(first_list);

    // print the second list
    printf("segunda");
    print_list(second_list);

    // print the third list
    printf("terceira");
    print_list(third_list);

    free_list(original_list);
    free_list(first_list);
    free_list(second_list);
    free_list(third_list);

    return 0;
}