#include <stdlib.h>
#include <string.h>
#include "TreeAVL.h"
#include "MallocUtils.h"

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

TreeAVLNode *new_node(char file_name[25]) {
    TreeAVLNode *node = malloc(sizeof(TreeAVLNode));
    validate_malloc(node);

    node->balancing_factor = 0;
    node->left = NULL;
    node->right = NULL;
    strcpy(node->file_name, file_name);
    node->count = 1;

    return node;
}

TreeAVLNode *rotate_to_left(TreeAVLNode *node) {
    TreeAVLNode *aux;
    aux = node->right;

    if (aux->balancing_factor == 1) {
        node->balancing_factor = -1;
    } else {
        node->balancing_factor = 0;
    }

    node->right = aux->left;
    aux->left = node;

    return aux;
}

TreeAVLNode *rotate_to_right(TreeAVLNode *node) {
    TreeAVLNode *aux;
    aux = node->left;

    if (aux->balancing_factor == -1) {
        node->balancing_factor = 1;
    } else {
        node->balancing_factor = 0;
    }

    node->left = aux->right;
    aux->right = node;

    return aux;
}

char do_add(TreeAVLNode *node, char file_name[25]) {
    int names_comparation = strcmp(node->file_name, file_name);
    char did_height_grow = 0;

    if (names_comparation == 0) {
        node->count++;
        return 0;
    } else if (names_comparation > 0) {
        // pra esquerda
        if (node->left == NULL) {
            node->left = new_node(file_name);

            if (node->balancing_factor == 0) {
                did_height_grow = 1;
            }

            node->balancing_factor--;
        } else {
            did_height_grow = do_add(node->left, file_name);

            if (did_height_grow) {
                node->balancing_factor--;
            }

            if (node->balancing_factor < -1) {
                if (node->right->balancing_factor > 0) {
                    node->left = rotate_to_right(node->left);
                }
                rotate_to_right(node);
                did_height_grow = 0;
            }
        }

    } else {
        if (node->right == NULL) {
            node->right = new_node(file_name);

            if (node->balancing_factor == 0) {
                did_height_grow = 1;
            }

            node->balancing_factor++;
        } else {
            did_height_grow = do_add(node->right, file_name);

            if (did_height_grow) {
                node->balancing_factor++;
            }

            if (node->balancing_factor > 1) {

                if (node->right->balancing_factor < 0) {
                    node->right = rotate_to_right(node->right);
                }

                rotate_to_left(node);
                did_height_grow = 0;
            }
        }
    }

    return did_height_grow;
}

void insert_to_tree(TreeAVL *tree, char *file_name) {
    if (tree->root == NULL) {
        tree->root = new_node(file_name);
    } else {
        do_add(tree->root, file_name);
    }
}

void remove_from_tree(TreeAVL *tree, char *file_name) {

}



char **get(TreeAVL *tree, char file_name[25]) {
    return NULL;
}
