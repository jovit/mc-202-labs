#ifndef TREEAVL_H
#define TREEAVL_H

typedef struct TreeAVLNode {
    char file_name[25];
    int count;
    struct TreeAVLNode *left, *right;
    int balancing_factor;
} TreeAVLNode;

typedef struct {
    TreeAVLNode *root;
} TreeAVL;

TreeAVL *create_tree();
void insert_to_tree(TreeAVL *tree, char *file_name);
void remove_from_tree(TreeAVL *tree, char *file_name);
void free_tree(TreeAVL* tree);
char **get(TreeAVL* tree, char file_name[25]);

#endif
