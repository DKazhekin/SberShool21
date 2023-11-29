#ifndef STACK_MODULE_H
#define STACK_MODULE_H
typedef struct node {
    char *str;
    struct node *next;
} NODE;

typedef struct stack {
    int count;
    struct node *top;
} STACK;

STACK *init(char *str);
char *pop(STACK *stack);
void push(STACK *stack, char *str);
void destroy(STACK *stack);

#endif
