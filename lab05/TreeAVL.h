#ifndef TREEAVL_H
#define TREEAVL_H

#define FILE_NAME_SIZE 26

typedef struct TreeAVLNode {
    char file_name[FILE_NAME_SIZE];
    int count;
    struct TreeAVLNode *left, *right;
    int height;
} TreeAVLNode;

typedef struct {
    TreeAVLNode *root;
} TreeAVL;

TreeAVL *create_tree();
void insert_to_tree(TreeAVL *tree, char file_name[FILE_NAME_SIZE]);
// remove nodes that match the expression
char remove_from_tree(TreeAVL *tree, char expression[FILE_NAME_SIZE]);
void free_tree(TreeAVL* tree);
// list the nodes that match the expression
char list(TreeAVL* tree, char expression[FILE_NAME_SIZE]);

#endif
