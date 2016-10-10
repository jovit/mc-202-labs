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
void add(TreeAVL *tree, char file_name[25]);
void remove(TreeAVL *tree, char file_name[25]);
void free_tree(TreeAVL* tree);
char **get(TreeAVL* tree, char file_name[25]);

#endif
