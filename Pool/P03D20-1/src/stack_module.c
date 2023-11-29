#include "stack_module.h"

#include <stdlib.h>

STACK *init(char *str) {
    STACK *stack = malloc(sizeof(STACK));
    NODE *node = malloc(sizeof(NODE));
    stack->count = 1;
    stack->top = node;
    stack->top->str = str;
    stack->top->next = NULL;
    return stack;
}

void push(STACK *stack, char *str) {
    NODE *node = malloc(sizeof(NODE));
    node->str = str;
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

char *pop(STACK *stack) {
    NODE *tmp = stack->top;
    if (stack->count == 0) {
        return NULL;
    } else if (stack->count == 1) {
        stack->count = 0;
        char *str = stack->top->str;
        free(stack->top);
        stack->top = NULL;
        return str;
    } else {
        stack->count--;
        while (tmp->next->next != NULL) {
            tmp = tmp->next;
        }
        char *str = tmp->next->str;
        free(tmp->next);
        tmp->next = NULL;
        return str;
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
