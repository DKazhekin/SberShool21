#include "stack.h"

#include <stdlib.h>

STACK *init(int value) {
    STACK *stack = malloc(sizeof(STACK));
    NODE *node = malloc(sizeof(NODE));
    stack->count = 1;
    stack->top = node;
    stack->top->value = value;
    stack->top->next = NULL;
    return stack;
}

void push(STACK *stack, int value) {
    NODE *node = malloc(sizeof(NODE));
    node->value = value;
    node->next = NULL;
    if (stack->count == 0) {
        stack->top = node;
    } else {
        NODE *tmp = stack->top;
        while (tmp->next != NULL) {
            tmp = tmp->next;
        }
        tmp->next = node;
    }
    stack->count++;
}

int pop(STACK *stack) {
    NODE *tmp = stack->top;
    if (stack->count == 0) {
        return -1;
    } else if (stack->count == 1) {
        stack->count = 0;
        int value = stack->top->value;
        free(stack->top);
        stack->top = NULL;
        return value;
    } else {
        stack->count--;
        ;
        while (tmp->next->next != NULL) {
            tmp = tmp->next;
        }
        int value = tmp->next->value;
        free(tmp->next);
        tmp->next = NULL;
        return value;
    }
}
void destroy(STACK *stack) {
    while (stack->top != NULL) {
        NODE *tmp = stack->top->next;
        free(stack->top);
        stack->top = tmp;
    }
    free(stack);
}