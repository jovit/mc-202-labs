#include <stdlib.h>
#include <string.h>
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
TreeAVLNode *new_node(unsigned long key, unsigned long parent) {
    TreeAVLNode *node = malloc(sizeof(TreeAVLNode));
    validate_malloc(node);

    node->height = 1;
    node->left = NULL;
    node->right = NULL;
    node->key = key;
    node->count = 1;
    node->parent = parent;

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
TreeAVLNode *do_add(TreeAVLNode *node, unsigned long key, unsigned long parent) {

    if (node == NULL) { // empty tree
        return new_node(key, parent);
    } else {
        if (node->key == key) { // repeated key
            node->count++;
            node->parent = parent;
        } else if (node->key > key) { // add in the left
            node->left = do_add(node->left, key, parent);
        } else { // add in the right
            node->right = do_add(node->right, key, parent);
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

void insert_to_tree(TreeAVL *tree, unsigned long key, unsigned long parent) {
    tree->root = do_add(tree->root, key, parent);
}

unsigned long do_get_parent(TreeAVLNode *node, long key) {
    if (node == NULL) {
        return 0;
    }

    if (node->key == key) {
        return node->parent;
    } else if (node->key > key) {
        return do_get_parent(node->left, key);
    } else {
        return do_get_parent(node->right, key);
    }
}

unsigned long get_parent(TreeAVL *tree, unsigned long key) {
    return do_get_parent(tree->root, key);
}

int do_get_count(TreeAVLNode *node, long key) {
    if (node == NULL) {
        return 0;
    }

    if (node->key == key) {
        return node->count;
    } else if (node->key > key) {
        return do_get_count(node->left, key);
    } else {
        return do_get_count(node->right, key);
    }
}

int get_count(TreeAVL *tree, unsigned long key) {
    return do_get_count(tree->root, key);
}

int do_get_total_count(TreeAVLNode *node) {
    if (node == NULL) {
        return 0;
    }

    return do_get_total_count(node->left) + do_get_total_count(node->right) + node->count;
}