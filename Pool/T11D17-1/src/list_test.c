#include "list.h"

#include <stdio.h>

void add_door_test();
void remove_door_test();

int main(void) {
    add_door_test();
    remove_door_test();
    return 0;
}

void add_door_test() {
    DOOR door1 = {1, 1}, door2 = {2, 0}, door3 = {3, 1}, door4 = {4, 0}, door5 = {5, 1}, door6 = {6, 0},
         door7 = {7, 1};

    const int answers[] = {1, 6, 7, 5, 2, 3, 4};
    int output[7];

    NODE *root = init(&door1);

    add_door(root, &door2);
    add_door(root->next, &door3);
    add_door(root->next->next, &door4);
    find_door(3, root);
    add_door(root, &door5);
    add_door(root, &door6);
    add_door(root->next, &door7);

    size_t index = 0;
    NODE *tmp = root;
    while (tmp != NULL) {
        output[index] = tmp->door.id;
        tmp = tmp->next;
        index++;
    }

    int result = 1;
    for (int i = 0; i < 7; i++) {
        if (answers[i] != output[i]) {
            result = 0;
        }
    }
    destroy(root);
    result ? printf("SUCCESS\n") : printf("FAIL\n");
}

void remove_door_test() {
    DOOR door1 = {1, 1}, door2 = {2, 0}, door3 = {3, 1}, door4 = {4, 0}, door5 = {5, 1}, door6 = {6, 0},
         door7 = {7, 1};

    const int answers[] = {1, 5, 2, 4};
    int output[4];

    NODE *root = init(&door1);

    add_door(root, &door2);
    add_door(root->next, &door3);
    add_door(root->next->next, &door4);
    add_door(root, &door5);
    add_door(root, &door6);
    add_door(root->next, &door7);
    remove_door(root->next->next->next->next->next, root);
    remove_door(root->next->next, root);
    remove_door(root->next, root);

    int index = 0;
    NODE *tmp = root;
    while (tmp != NULL) {
        output[index] = tmp->door.id;
        tmp = tmp->next;
        index++;
    }
    int result = 1;

    for (int i = 0; i < 4; i++) {
        if (answers[i] != output[i]) {
            result = 0;
        }
    }
    destroy(root);
    result ? printf("SUCCESS") : printf("FAIL");
}