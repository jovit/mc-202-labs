#include <stdio.h>
#include <string.h>
#include "TreeAVL.h"

#define TOUCH "touch"
#define LIST "ls"
#define REMOVE "rm"
#define NO_FILES_WITH_THIS_EXPRESSION "nao existem arquivos com essa expressao\n"

int main(void) {
    char command_read[25];
    char file_name[25];
    TreeAVL *tree = create_tree();

    // while hasn't finished reading values
    while (scanf(" %s %s", command_read, file_name) != EOF) {
        if (strcmp(TOUCH, command_read) == 0) {
            insert_to_tree(tree, file_name);
        } else if (strcmp(LIST, command_read) == 0) {
            if (!list(tree, file_name)) {
                printf(NO_FILES_WITH_THIS_EXPRESSION);
            }
        } else if (strcmp(REMOVE, command_read) == 0) {
            if (!remove_from_tree(tree, file_name)) {
               printf(NO_FILES_WITH_THIS_EXPRESSION);
            }
        }
    }

    free_tree(tree);

    return 0;
}