#include <stdio.h>

#include "bst.h"

void insert_node_test();

int main() {
    insert_node_test();
    return 0;
}

void insert_node_test() {
    t_btree *root = bstree_create_node(10);
    bstree_insert(root, 15, cmp);
    bstree_insert(root, 20, cmp);
    bstree_insert(root, 25, cmp);
    bstree_insert(root, 30, cmp);
    bstree_insert(root, 35, cmp);

    const int answers[] = {10, 15, 20, 25, 30, 35};
    t_btree *results[] = {root,
                          root->right,
                          root->right->right,
                          root->right->right->right,
                          root->right->right->right->right,
                          root->right->right->right->right->right};

    int flag = 1;
    for (int i = 0; i < 6; i++) {
        if (answers[i] != results[i]->value) {
            flag = 0;
        }
    }
    flag ? printf("SUCCESS") : printf("FAIL");
    freeTree(root);
}