#ifndef TREEAVL_H
#define TREEAVL_H


typedef struct TreeAVLNode {
    long key;
    struct TreeAVLNode *left, *right;
    int height;
} TreeAVLNode;

typedef struct {
    TreeAVLNode *root;
} TreeAVL;

TreeAVL *create_tree();
void insert_to_tree(TreeAVL *tree, long key);
void free_tree(TreeAVL* tree);
char contains(TreeAVL* tree, long key);

#endif
