#ifndef INTLIST_H
#define INTLIST_H
typedef struct LongListNode {
    unsigned long value;
    int count;
    struct LongListNode *next;
} LongListNode;

typedef struct {
    LongListNode *root;
} LongList;

LongList *create_list();
void add_to_start(LongList *list, unsigned long value);
void free_list(LongList *list);

#endif
