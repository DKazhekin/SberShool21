#ifndef STACK_H
#define STACK_H

typedef struct node {
    int value;
    struct node *next;
} NODE;

typedef struct stack {
    int count;
    struct node *top;
} STACK;

STACK *init(int value);
int pop(STACK *stack);
void push(STACK *stack, int value);
void destroy(STACK *stack);

#endif