#include <stdlib.h>
#include <string.h>
#include "SplayTree.h"
#include "Utils.h"

SplayTreeNode *new_splay_tree_node(char *ingredient_name) {
    SplayTreeNode *new_node = malloc(sizeof(SplayTreeNode));

    validate_malloc(new_node);

    strcpy(new_node->ingredient_name, ingredient_name);
    new_node->ingredients_queue = create_queue();

    insert_to_queue(new_node->ingredients_queue, create_ingredient(ingredient_name, -2));
    insert_to_queue(new_node->ingredients_queue, create_ingredient(ingredient_name, -2));

    new_node->pizzas_waiting = 0;
    new_node->right = NULL;
    new_node->left = NULL;

    return new_node;
}

SplayTree *create_splay_tree() {
    SplayTree *new_tree = malloc(sizeof(SplayTree));

    validate_malloc(new_tree);
    new_tree->root = NULL;

    return new_tree;
}

SplayTreeNode *rotate_to_right(SplayTreeNode *node) {
    SplayTreeNode *aux = node->left;

    aux->right = node;
    node->left = aux->right;

    return aux;
}

SplayTreeNode *rotate_to_left(SplayTreeNode *node) {
    SplayTreeNode *aux = node->left;

    aux->right = node;
    node->left = aux->right;

    return aux;
}

SplayTreeNode *splay(SplayTreeNode *root, char *ingredient_name) {
    if (root == NULL) {
        return NULL;
    } else {
        int comparison = strcmp(root->ingredient_name, ingredient_name);

        if (comparison == 0) {
            return root;
        } else if (comparison < 0) { // value on the right
            if (root->right != NULL) {
                comparison = strcmp(root->right->ingredient_name, ingredient_name);

                if (comparison == 0) { // Zag
                    root = rotate_to_left(root);
                } else if (comparison < 0) { // Zag-Zag
                    root->right->right = splay(root->right->right, ingredient_name); // bring value to right tree
                    root = rotate_to_left(root);

                    root = root->right != NULL ? rotate_to_left(root) : root;
                } else if (comparison > 0) { // Zig-Zag
                    root->right->left = splay(root->right->left, ingredient_name); // bring value to the left tree
                    root->right = root->right->left != NULL ? rotate_to_right(root->right) : root->right;

                    root = root->right != NULL ? rotate_to_left(root) : root;
                }

            }
        } else if (comparison > 0) { // value on the left
            if (root->left != NULL) {
                comparison = strcmp(root->left->ingredient_name, ingredient_name);

                if (comparison == 0) { // Zig
                    root = rotate_to_right(root);
                } else if (comparison < 0) { // Zag-Zig
                    root->left->right = splay(root->right->right, ingredient_name); // bring value to right tree
                    root->left = root->left->right != NULL ? rotate_to_left(root->left) : root->left;

                    root = root->left != NULL ? rotate_to_right(root) : root;
                } else if (comparison > 0) { // Zig-Zig
                    root->left->left = splay(root->left->left, ingredient_name); // bring value to the left tree
                    root = rotate_to_right(root);

                    root = root->left != NULL ? rotate_to_right(root) : root;
                }

            }
        }
    }

    return root;
}

SplayTreeNode *search(SplayTree *tree, char *ingredient_name) {
    int comparison;

    if (tree->root != NULL) {
        tree->root = splay(tree->root, ingredient_name);
        comparison = strcmp(tree->root->ingredient_name, ingredient_name);

        if (comparison == 0) {
            return tree->root;
        }
    }

    return NULL;
}

SplayTreeNode *do_insert(SplayTreeNode *current_node, char *ingredient_name) {
    int comparison;

    if (current_node == NULL) {
        return new_splay_tree_node(ingredient_name);
    }

    comparison = strcmp(current_node->ingredient_name, ingredient_name);

    if (comparison < 0) {
        current_node->right = do_insert(current_node->right, ingredient_name);
    } else if (comparison > 0) {
        current_node->left = do_insert(current_node->left, ingredient_name);
    }

    return current_node;
}

void insert(SplayTree *tree, char *ingredient_name) {
    tree->root = do_insert(tree->root, ingredient_name);
    tree->root = splay(tree->root, ingredient_name);
}

char can_use_ingredient(SplayTree *tree, char *ingredient_name, int time) {
    SplayTreeNode *ingredient_node;
    Ingredient *first_ingredient;

    ingredient_node = search(tree, ingredient_name);

    if (ingredient_node == NULL) { // if the ingredient hasn't been used yet
        insert(tree, ingredient_name);
    }

    ingredient_node = search(tree, ingredient_name);

    if (is_queue_empty(ingredient_node->ingredients_queue)) {
        ingredient_node->pizzas_waiting++;
        insert_to_queue(ingredient_node->ingredients_queue, create_ingredient(ingredient_name, time));
        return 0;
    } else {
        first_ingredient = peek_queue(ingredient_node->ingredients_queue);
        if (should_be_stored(first_ingredient, time) && ingredient_node->pizzas_waiting == 0) {
            remove_from_queue(ingredient_node->ingredients_queue);
            free(first_ingredient);
            return can_use_ingredient(tree, ingredient_name, time);
        } else {
            ingredient_node->pizzas_waiting++;
            return is_unfrozen(first_ingredient, time);
        }
    }
}

void use_ingredient(SplayTree *tree, char *ingredient_name, int time) {
    SplayTreeNode *ingredient_node;
    Ingredient *first_ingredient;

    ingredient_node = search(tree, ingredient_name);

    first_ingredient = remove_from_queue(ingredient_node->ingredients_queue);
    free(first_ingredient);

    insert_to_queue(ingredient_node->ingredients_queue, create_ingredient(ingredient_name, time));
}
