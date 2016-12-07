#ifndef TREEAVL_H
#define TREEAVL_H


typedef struct TreeAVLNode {
    unsigned long key;
    unsigned long parent;
    struct TreeAVLNode *left, *right;
    int height;
    int count;
} TreeAVLNode;

typedef struct {
    TreeAVLNode *root;
} TreeAVL;

TreeAVL *create_tree();
void insert_to_tree(TreeAVL *tree, unsigned long key, unsigned long parent);
int get_count(TreeAVL *tree, unsigned long key);
unsigned long get_parent(TreeAVL *tree, unsigned long key);
void free_tree(TreeAVL* tree);

#endif
