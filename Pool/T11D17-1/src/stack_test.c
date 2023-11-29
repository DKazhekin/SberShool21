#include "stack.h"

#include <stdio.h>

void push_test();
void pop_test();

int main(void) {
    pop_test();
    push_test();
    return 0;
}

void pop_test() {
    const int answers[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int results[8];

    STACK *stack = init(1);
    push(stack, 2);
    push(stack, 3);
    push(stack, 4);
    push(stack, 5);
    push(stack, 6);
    push(stack, 7);
    push(stack, 8);

    int index = 0;
    NODE *tmp = stack->top;
    while (tmp != NULL) {
        results[index] = tmp->value;
        tmp = tmp->next;
        index++;
    }

    int result = 1;
    for (int i = 0; i < 8; i++) {
        if (answers[i] != results[i]) {
            result = 0;
        }
    }
    destroy(stack);
    result ? printf("SUCCESS\n") : printf("FAIL\n");
}

void push_test() {
    const int answers[] = {1, 2, 3};
    int results[3];

    STACK *stack = init(1);
    push(stack, 2);
    push(stack, 3);
    push(stack, 4);
    push(stack, 5);
    push(stack, 6);
    push(stack, 7);
    push(stack, 8);
    pop(stack);
    pop(stack);
    pop(stack);
    pop(stack);
    push(stack, 10);
    push(stack, 10);
    push(stack, 10);
    pop(stack);
    pop(stack);
    pop(stack);
    pop(stack);

    int index = 0;
    NODE *tmp = stack->top;
    while (tmp != NULL) {
        results[index] = tmp->value;
        tmp = tmp->next;
        index++;
    }

    int result = 1;
    for (int i = 0; i < 3; i++) {
        if (answers[i] != results[i]) {
            result = 0;
        }
    }
    destroy(stack);
    result ? printf("SUCCESS") : printf("FAIL");
}