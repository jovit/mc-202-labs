#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "TreeAVL.h"
#include "Utils.h"


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

    node->height = get_height(node);
    aux->height = get_height(aux);

    return aux;
}

TreeAVLNode *rotate_to_right(TreeAVLNode *node) {
    TreeAVLNode *aux;
    aux = node->left;

    node->left = aux->right;
    aux->right = node;

    node->height = get_height(node);
    aux->height = get_height(aux);

    return aux;
}


TreeAVLNode *do_add(TreeAVLNode *node, char file_name[FILE_NAME_SIZE]) {
    int names_comparation;

    if (node == NULL) {
        return new_node(file_name);
    } else {
        names_comparation = strcmp(node->file_name, file_name);

        if (names_comparation == 0) {
            node->count++;
        } else if (names_comparation > 0) {
            node->left = do_add(node->left, file_name);
        } else {
            node->right = do_add(node->right, file_name);
        }

        node->height = get_height(node);

        if (height_difference(node) > 1) {
            if (height_difference(node->right) < 0) {
                node->right = rotate_to_right(node->right);
            }
            node = rotate_to_left(node);
        } else if (height_difference(node) < -1) {
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

char match(char expression[FILE_NAME_SIZE], char file_name[FILE_NAME_SIZE]) {
    int length = (int) strlen(expression);
    int i;

    for (i = 0; i < length-1; i++) {
        if (expression[i] != file_name[i]) {
            return 0;
        }
    }

    return 1;
}

TreeAVLNode *delete_node(TreeAVLNode *node) {
    TreeAVLNode *aux, *aux_parent;
    char found;

    if (node->right == NULL && node->left == NULL) {
        free(node);
        return NULL;
    } else if( node->left == NULL || node->right == NULL) {
        if (node->left == NULL) {
            aux = node->left;
        } else {
            aux = node->right;
        }

        *node = *aux;

        free(aux);
    } else  {
        aux = node->right;
        aux_parent = node;

        while (aux->left != NULL) {
            aux_parent = aux;
            aux = aux->left;
        }

        strcpy(node->file_name, aux->file_name);

        node->right = do_remove(aux_parent, aux->file_name, &found);
    }

    node->height = get_height(node);

    if (height_difference(node) > 1) {
        if (height_difference(node->right) < 0) {
            node->right = rotate_to_right(node->right);
        }
        node = rotate_to_left(node);
    } else if (height_difference(node) < -1) {
        if (height_difference(node->left) > 0) {
            node->left = rotate_to_left(node->left);
        }
        node = rotate_to_right(node);
    }

    return node;
}

TreeAVLNode *do_remove(TreeAVLNode *node, char expression[FILE_NAME_SIZE], char *found) {
    int names_comparation;
    int file_name_size;

    if (node == NULL) {
        *found |= 0;
    } else {
        names_comparation = strcmp(node->file_name, expression);
        file_name_size = (int) strlen(expression);

        if (expression[file_name_size-1] == '*') {
            if (match(expression, node->file_name)) {
                *found = 1;

                node = delete_node(node);

                if (node != NULL && node->left != NULL && match(expression, node->left->file_name)){
                    node->left = do_remove(node->left, expression, found);
                }

                if (node != NULL && node->right != NULL && match(expression, node->right->file_name)){
                    node->right = do_remove(node->right, expression, found);
                }
            } else {
                node->right = do_remove(node->right, expression, found);
                node->left = do_remove(node->left, expression, found);
            }


        } else {
            if (names_comparation == 0) {
                *found = 1;
                node = delete_node(node);
            } else if (names_comparation < 0) {
                node->right = do_remove(node->right, expression, found);
            } else {
                node->left = do_remove(node->left, expression, found);
            }
        }
    }

    return node;
}

char remove_from_tree(TreeAVL *tree, char expression[FILE_NAME_SIZE]) {
    char found;
    do_remove(tree->root, expression, &found);
    return found;
}



char do_list(TreeAVLNode *node, char expression[FILE_NAME_SIZE]) {
    int names_comparation;
    int file_name_size;
    int i;
    char found = 0;

    if (node == NULL) {
        return 0;
    } else{
        names_comparation = strcmp(node->file_name, expression);
        file_name_size = (int) strlen(expression);

        if (expression[file_name_size-1] == '*') {
            if (match(expression, node->file_name)) {
                if (node->left != NULL && match(expression, node->left->file_name)){
                    found |= do_list(node->left, expression);
                }

                if (node->count > 0) {
                    for (i = 0; i < node->count; i++) {
                        printf("%s\n", node->file_name);
                    }
                    found = 1;
                }

                if (node->right != NULL && match(expression, node->right->file_name)){
                    found |= do_list(node->right, expression);
                }
            } else {
                found |= do_list(node->left, expression);
                found |= do_list(node->right, expression);
            }

            return found;
        } else {
            if (names_comparation == 0) {
                if (node->count > 0) {
                    for (i = 0; i < node->count; i++) {
                        printf("%s\n", node->file_name);
                    }
                    return 1;
                } else {
                    return 0;
                }
            } else if (names_comparation < 0) {
                return do_list(node->right, expression);
            } else {
                return do_list(node->left, expression);
            }
        }


    }
}

char list(TreeAVL *tree, char expression[FILE_NAME_SIZE]) {
    return do_list(tree->root, expression);
}
