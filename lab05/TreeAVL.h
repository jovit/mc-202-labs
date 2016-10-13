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
char remove_from_tree(TreeAVL *tree, char expression[FILE_NAME_SIZE]);
TreeAVLNode *do_remove(TreeAVLNode *node, char expression[FILE_NAME_SIZE], char *found);
void free_tree(TreeAVL* tree);
char list(TreeAVL* tree, char expression[FILE_NAME_SIZE]);

#endif
