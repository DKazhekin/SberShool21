#include <stdio.h>
#include <stdlib.h>

#include "bst.h"

void create_node_test();

int main() {
    create_node_test();
    return 0;
}

void create_node_test() {
    t_btree *node1 = bstree_create_node(10);
    t_btree *node2 = bstree_create_node(15);
    t_btree *node3 = bstree_create_node(20);
    t_btree *node4 = bstree_create_node(25);
    t_btree *node5 = bstree_create_node(30);
    t_btree *node6 = bstree_create_node(35);

    const int answers[] = {10, 15, 20, 25, 30, 35};
    t_btree *results[] = {node1, node2, node3, node4, node5, node6};

    int flag = 1;
    for (int i = 0; i < 6; i++) {
        if (answers[i] != results[i]->value) {
            flag = 0;
        }
    }
    flag ? printf("SUCCESS") : printf("FAIL");
    free(node1);
    free(node2);
    free(node3);
    free(node4);
    free(node5);
    free(node6);
}