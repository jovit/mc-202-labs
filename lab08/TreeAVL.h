#ifndef TREEAVL_H
#define TREEAVL_H


typedef struct TreeAVLNode {
    long key;
    struct TreeAVLNode *left, *right;
    int height;
    int count;
} TreeAVLNode;

typedef struct {
    TreeAVLNode *root;
} TreeAVL;

TreeAVL *create_tree();
void insert_to_tree(TreeAVL *tree, long key);
int get_count(TreeAVL *tree, long key);
int get_total_count(TreeAVL *tree);
void free_tree(TreeAVL* tree);

#endif
