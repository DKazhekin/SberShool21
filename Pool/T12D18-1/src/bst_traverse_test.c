#include <stdio.h>

#include "bst.h"

int main() {
    t_btree *root = bstree_create_node(10);
    bstree_insert(root, 30, cmp);
    bstree_insert(root, 15, cmp);
    bstree_insert(root, 35, cmp);
    bstree_insert(root, 20, cmp);
    bstree_insert(root, 25, cmp);

    bstree_apply_infix(root, apply);
    printf("\n");
    bstree_apply_postfix(root, apply);
    printf("\n");
    bstree_apply_prefix(root, apply);
    printf("\n");
    printf("SUCCESS");
    freeTree(root);
    return 0;
}