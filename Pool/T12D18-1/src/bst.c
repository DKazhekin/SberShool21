#include "bst.h"

#include <stdio.h>
#include <stdlib.h>

t_btree *bstree_create_node(int value) {
    t_btree *node = malloc(sizeof(t_btree));
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

t_btree *bstree_insert(t_btree *root, int item, int (*cmp)(int, int)) {
    if (root == NULL) {
        return bstree_create_node(item);
    }
    if (cmp(item, root->value) == -1) {
        root->right = bstree_insert(root->right, item, cmp);
    } else {
        root->left = bstree_insert(root->left, item, cmp);
    }
    return root;
}

int cmp(int a, int b) {
    if (a > b) {
        return -1;
    } else {
        return 1;
    }
}

void apply(int value) { printf("%d ", value); }

void bstree_apply_infix(t_btree *root, void (*apply)(int)) {
    if (root != NULL) {
        bstree_apply_infix(root->left, apply);
        apply(root->value);
        bstree_apply_infix(root->right, apply);
    }
}

void bstree_apply_prefix(t_btree *root, void (*apply)(int)) {
    if (root != NULL) {
        apply(root->value);
        bstree_apply_prefix(root->left, apply);
        bstree_apply_prefix(root->right, apply);
    }
}

void bstree_apply_postfix(t_btree *root, void (*apply)(int)) {
    if (root != NULL) {
        bstree_apply_postfix(root->left, apply);
        bstree_apply_postfix(root->right, apply);
        apply(root->value);
    }
}

void freeTree(t_btree *root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}
