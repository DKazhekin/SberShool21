#include "door_struct.h"
#ifndef LIST_H
#define LIST_H

typedef struct node {
    DOOR door;
    struct node *next;
} NODE;

NODE *init(const DOOR *door);
NODE *add_door(NODE *elem, const DOOR *door);
NODE *find_door(int door_id, NODE *root);
NODE *remove_door(NODE *elem, NODE *root);
void destroy(NODE *root);

#endif
