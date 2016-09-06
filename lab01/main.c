//
// Created by joao on 03/09/16.
//
#include <stdio.h>
#include <stdlib.h>

//----------------START OF IntList IMPLEMENTATION-------------------
typedef struct Node {
    struct Node* next;
    int value;
} Node;

typedef struct List {
    Node* first;
} IntList;


void validate_malloc(void *pointer) {
    if (pointer == NULL) {
        printf("Out of memory");
        exit(1);
    }
}

IntList* create_list() {
    IntList *new_list = malloc(sizeof(IntList));

    validate_malloc(new_list);

    new_list->first = NULL;

    return new_list;
}

void free_list(IntList* list) {
    Node *next ,*current = list->first;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    free(list);
}

void add_to_list(IntList* list, int value) {
    Node *current_node;
    Node *new_node = malloc(sizeof(Node));

    validate_malloc(new_node);

    new_node->value = value;

    if (list->first == NULL) {
        list->first = new_node;
    } else {
        current_node = list->first;

        while (current_node->next != NULL) {
            current_node = current_node->next;
        }
        current_node->next = new_node;
    }
}
//----------------END OF IntList IMPLEMENTATION-------------------

Node* find_node(Node *start, int value) {
    Node *current_node = start;

    while (current_node != NULL && current_node->value != value) {
        current_node = current_node->next;
    }

    return current_node;
}

Node* get_first_list_start(IntList *original_list, int m, int n, int p) {
    Node *starting_node;
    starting_node = find_node(original_list->first, m);

    if (starting_node == NULL) {
        starting_node = original_list->first;
    }

    return starting_node;
}

Node* get_second_list_start(IntList *original_list, int m, int n, int p) {
    Node *starting_node, *first_list_start;
    first_list_start = get_first_list_start(original_list, m, n, p);

    starting_node = find_node(first_list_start, n);

    if (starting_node == NULL) {
        starting_node = first_list_start;
    }


    return starting_node;
}

Node* get_third_list_start(IntList *original_list, int m, int n, int p) {
    Node *starting_node, *second_list_start;

    second_list_start = get_second_list_start(original_list, m, n, p);

    starting_node = find_node(second_list_start, p);

    if (starting_node == NULL) {
        starting_node = second_list_start;
    }


    return starting_node;
}

IntList* get_first_list(IntList *original_list, int m, int n, int p) {
    Node *starting_node, *ending_node, *current_node;
    IntList *first_list;

    first_list = create_list();

    starting_node = get_first_list_start(original_list, m, n, p);
    ending_node = find_node(starting_node, n);

    if(ending_node == NULL) {
        ending_node = find_node(starting_node, p);
    }

    current_node = starting_node;

    while (current_node != ending_node) {
        add_to_list(first_list, current_node->value);
        current_node = current_node->next;
    }

    if (current_node != NULL) {
        add_to_list(first_list, current_node->value);
    }

    return first_list;
}

IntList* get_second_list(IntList *original_list, int m, int n, int p) {
    Node *starting_node, *ending_node, *current_node;
    IntList *second_list;

    second_list = create_list();

    starting_node = get_second_list_start(original_list, m, n, p);

    ending_node = find_node(starting_node, p);

    current_node = starting_node;

    while (current_node != ending_node) {
        add_to_list(second_list, current_node->value);
        current_node = current_node->next;
    }

    if (current_node != NULL) {
        add_to_list(second_list, current_node->value);
    }

    return second_list;
}

IntList* get_third_list(IntList *original_list, int m, int n, int p) {
    Node *starting_node, *current_node;
    IntList *third_list;

    third_list = create_list();

    starting_node = get_third_list_start(original_list, m, n, p);

    current_node = starting_node;

    while (current_node != NULL) {
        add_to_list(third_list, current_node->value);
        current_node = current_node->next;
    }

    return third_list;
}

void print_list(IntList *list) {
    Node *current_node;

    for (current_node = list->first; current_node != NULL; current_node = current_node->next) {
        printf(" %d", current_node->value);
    }

    printf("\n");
}

int main(void) {https://issues.movile.com/browse/TI-6811
    int number_read, m, n, p;
    char char_read = ' ';
    IntList *original_list, *first_list, *second_list, *third_list;

    original_list = create_list();

    while (char_read == ' ') {
        scanf("%d%c", &number_read, &char_read);
        add_to_list(original_list, number_read);
    }

    scanf("%d %d %d", &m, &n ,&p);

    first_list = get_first_list(original_list, m, n, p);
    second_list = get_second_list(original_list, m, n, p);
    third_list = get_third_list(original_list, m, n, p);

    printf("original");
    print_list(original_list);

    printf("m=%d, n=%d, p=%d\n", m, n, p);

    printf("primeira");
    print_list(first_list);

    printf("segunda");
    print_list(second_list);

    printf("terceira");
    print_list(third_list);

    free_list(original_list);
    free_list(first_list);
    free_list(second_list);
    free_list(third_list);

    return 0;
}