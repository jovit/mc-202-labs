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
TreeAVLNode *new_node(long key) {
    TreeAVLNode *node = malloc(sizeof(TreeAVLNode));
    validate_malloc(node);

    node->height = 1;
    node->left = NULL;
    node->right = NULL;
    node->key = key;

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
TreeAVLNode *do_add(TreeAVLNode *node, long key) {
    if (node == NULL) { // empty tree
        return new_node(key);
    } else {
        if (node->key > key) { // add in the left
            node->left = do_add(node->left, key);
        } else  if (node->key < key) { // add in the right
            node->right = do_add(node->right, key);
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

void insert_to_tree(TreeAVL *tree, long key) {
    tree->root = do_add(tree->root, key);
}

char do_contains(TreeAVLNode *node, long key)  {
    if (node == NULL) { // empty tree
        return 0;
    } else {
        if (node->key == key) {
          return 1;
        } else if (node->key > key) { // add in the left
            return do_contains(node->left, key);
        } else  if (node->key < key) { // add in the right
            return do_contains(node->right, key);
        }

    }
}

char contains(TreeAVL *tree, long key) {
    return do_contains(tree->root, key);
}
