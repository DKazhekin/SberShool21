#include "list.h"

#include <stdlib.h>

#include "door_struct.h"

NODE *init(const DOOR *door) {
    NODE *root = malloc(sizeof(NODE));
    root->door = *door;
    root->next = NULL;
    return root;
}

NODE *add_door(NODE *elem, const DOOR *door) {
    NODE *new = malloc(sizeof(NODE));
    new->next = elem->next;
    new->door = *door;
    elem->next = new;
    return new;
}

NODE *find_door(int door_id, NODE *root) {
    if (root->door.id == door_id) {
        return root;
    }
    while (root->next != NULL) {
        if (root->door.id == door_id) {
            return root;
        }
        root = root->next;
    }
    if (root->door.id == door_id) {
        return root;
    }
    return NULL;
}

NODE *remove_door(NODE *elem, NODE *root) {
    // Проверка на то, что сразу нужно удалять нулевой элемент
    NODE *tmp = NULL;
    if (root == elem) {
        tmp = root->next;
        free(root);
        root = tmp;
        return root;
    }

    // Проход для удаления любого промежуточного узла
    tmp = root;
    while (tmp->next != elem && tmp->next != NULL) {
        tmp = tmp->next;
    }

    // Проверка на то что удаляемого элемента нет в списке
    if (tmp->next == NULL) {
        return NULL;
    }

    // Проверка на удаление последнего элемента
    if (tmp->next->next == NULL) {
        free(tmp->next);
        tmp->next = NULL;
    }
    // Или если это обычный промежуточный узел
    else {
        NODE *tmp2 = NULL;
        tmp2 = tmp->next->next;
        free(tmp->next);
        tmp->next = tmp2;
    }
    return tmp;
}

void destroy(NODE *root) {
    while (root != NULL) {
        NODE *tmp = root->next;
        free(root);
        root = tmp;
    }
}