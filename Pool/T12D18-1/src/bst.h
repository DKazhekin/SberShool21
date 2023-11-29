#ifndef SRC_BST_H
#define SRC_BST_H

typedef struct t_btree {
    int value;
    struct t_btree *left;
    struct t_btree *right;
} t_btree;

t_btree *bstree_create_node(int item);
t_btree *bstree_insert(t_btree *root, int item, int (*cmp)(int, int));
int cmp(int a, int b);
void bstree_apply_infix(t_btree *root, void (*apply)(int));
void bstree_apply_prefix(t_btree *root, void (*apply)(int));
void bstree_apply_postfix(t_btree *root, void (*apply)(int));
void apply(int value);
void freeTree(t_btree *root);

#endif
