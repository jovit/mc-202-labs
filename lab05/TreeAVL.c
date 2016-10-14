#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "TreeAVL.h"
#include "Utils.h"

// get's the height difference between the two children of the node
int height_difference(TreeAVLNode *node) {
    int right_height = 0, left_height = 0;
    if (node->left) {
        left_height = node->left->height;
    }

    if (node->right) {
        right_height = node->right->height;
    }

    return right_height - left_height;
}

// gets the height of a node based on the heights of its children
int get_height(TreeAVLNode *node) {
    int right_height = 0, left_height = 0;
    if (node->left) {
        left_height = node->left->height;
    }

    if (node->right) {
        right_height = node->right->height;
    }

    if (right_height > left_height) {
        return right_height + 1;
    } else {
        return left_height + 1;
    }
}

TreeAVL *create_tree() {
    TreeAVL *new_tree = malloc(sizeof(TreeAVL));
    validate_malloc(new_tree);
    new_tree->root = NULL;
    return new_tree;
}

// frees the nodes from a tree
void free_tree_node(TreeAVLNode *node) {
    if (node != NULL) {
        free_tree_node(node->right);
        free_tree_node(node->left);
        free(node);
    }
}

void free_tree(TreeAVL *tree) {
    if (tree != NULL) {
        free_tree_node(tree->root);
        free(tree);
    }
}

// initializes a new node
TreeAVLNode *new_node(char file_name[FILE_NAME_SIZE]) {
    TreeAVLNode *node = malloc(sizeof(TreeAVLNode));
    validate_malloc(node);

    node->height = 1;
    node->left = NULL;
    node->right = NULL;
    strcpy(node->file_name, file_name);
    node->count = 1;

    return node;
}

TreeAVLNode *rotate_to_left(TreeAVLNode *node) {
    TreeAVLNode *aux;
    aux = node->right;

    node->right = aux->left;
    aux->left = node;

    // update the heights
    node->height = get_height(node);
    aux->height = get_height(aux);

    return aux;
}

TreeAVLNode *rotate_to_right(TreeAVLNode *node) {
    TreeAVLNode *aux;
    aux = node->left;

    node->left = aux->right;
    aux->right = node;

    // update the heights
    node->height = get_height(node);
    aux->height = get_height(aux);

    return aux;
}

// companion recursive function to insert_to_tree
TreeAVLNode *do_add(TreeAVLNode *node, char file_name[FILE_NAME_SIZE]) {
    int names_comparison;

    if (node == NULL) { // empty tree
        return new_node(file_name);
    } else {
        names_comparison = strcmp(node->file_name, file_name);

        if (names_comparison == 0) { // repeated file name
            node->count++;
        } else if (names_comparison > 0) { // add in the left
            node->left = do_add(node->left, file_name);
        } else { // add in the right
            node->right = do_add(node->right, file_name);
        }

        // update the height
        node->height = get_height(node);

        // check balance
        if (height_difference(node) > 1) { // if unbalanced to the right
            if (height_difference(node->right) < 0) {
                node->right = rotate_to_right(node->right);
            }
            node = rotate_to_left(node);
        } else if (height_difference(node) < -1) { // if unbalanced to the left
            if (height_difference(node->left) > 0) {
                node->left = rotate_to_left(node->left);
            }
            node = rotate_to_right(node);
        }

    }

    return node;
}

void insert_to_tree(TreeAVL *tree, char *file_name) {
    tree->root = do_add(tree->root, file_name);
}

// check if string matches expression
char match(char expression[FILE_NAME_SIZE], char file_name[FILE_NAME_SIZE]) {
    int length = strlen(expression);
    int i;

    for (i = 0; i < length; i++) {
        if (expression[i] != file_name[i]) {
            return 0;
        }
    }

    return 1;
}

// companion recursive function to remove_from_tree
char do_remove(TreeAVLNode *node, char expression[FILE_NAME_SIZE]) {
    int names_comparison;
    int file_name_size;
    char found = 0;

    if (node == NULL) { // if the tree is empty
        return 0;
    } else {
        names_comparison = strcmp(node->file_name, expression);
        file_name_size = (int) strlen(expression);

        if (expression[file_name_size-1] == '*') { // if it's an expression
            expression[file_name_size-1] = '\0';

            if (match(expression, node->file_name)) { // check if found a matching candidate
                if (node->count > 0) {
                    node->count = 0;
                    found = 1;
                }
            }

            expression[file_name_size-1] = '*';

            // search on the whole tree
            found |= do_remove(node->right, expression);
            found |= do_remove(node->left, expression);

            return found;
        } else { // if it's looking for the exact file name
            if (names_comparison == 0) { // if found
                if (node->count > 0) {
                    node->count = 0;
                    return 1;
                } else {
                    return 0;
                }
            }

            if (names_comparison < 0) { // remove from the right
                return do_remove(node->right, expression);
            } else { // remove from the left
                return do_remove(node->left, expression);
            }
        }
    }
}

char remove_from_tree(TreeAVL *tree, char expression[FILE_NAME_SIZE]) {
    return do_remove(tree->root, expression);
}

// companion recursive function to list
char do_list(TreeAVLNode *node, char expression[FILE_NAME_SIZE]) {
    int names_comparation;
    int file_name_size;
    int i;
    char found = 0;

    if (node == NULL) { // if the tree is empty
        return 0;
    } else{
        names_comparation = strcmp(node->file_name, expression);
        file_name_size = (int) strlen(expression);

        if (expression[file_name_size-1] == '*') { // if it's an expression
            found |= do_list(node->left, expression); // check the left tree first

            expression[file_name_size-1] = '\0';

            if (match(expression, node->file_name)) { // check if current node matches the expression
                if (node->count > 0) {
                    for (i = 0; i < node->count; i++) { // print the corresponding count of files
                        printf("%s\n", node->file_name);
                    }
                    found = 1;
                }
            }

            expression[file_name_size-1] = '*';

            found |= do_list(node->right, expression); // check the right tree

            return found;
        } else { // if it's looking for an exact name
            if (names_comparation == 0) { // if found the file
                if (node->count > 0) {
                    for (i = 0; i < node->count; i++) {
                        printf("%s\n", node->file_name);
                    }
                    return 1;
                } else {
                    return 0;
                }
            }

            if (names_comparation < 0) { // if the file is on the right
                return do_list(node->right, expression);
            } else {// if the file is on the left
                return do_list(node->left, expression);
            }
        }


    }
}

char list(TreeAVL *tree, char expression[FILE_NAME_SIZE]) {
    return do_list(tree->root, expression);
}
