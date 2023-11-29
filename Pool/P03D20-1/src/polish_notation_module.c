#include "polish_notation_module.h"

#include <stdlib.h>
#include <string.h>

#include "stack_module.h"
#define MESS ""

char **infix_to_postfix(char **tokens, int *num_tokens) {
    int brackets_count = 0;
    for (int i = 0; i < *num_tokens; i++) {
        if (strcmp(tokens[i], "(") == 0 || strcmp(tokens[i], ")") == 0) brackets_count++;
    }
    // Создаем выходной массив токенов и инициализируем стек операторов
    char **postfix_array = malloc((*num_tokens - brackets_count) * sizeof(char *));
    STACK *operator_stack = init(MESS);
    pop(operator_stack);

    int index = 0;
    for (char **token = tokens; token - tokens < *num_tokens; token++) {
        // Обработка случая открывающейся скобки
        if (strcmp(*token, "(") == 0) {
            push(operator_stack, "(");
        }
        // Обработка случая закрывающейся скобки
        else if (strcmp(*token, ")") == 0) {
            char *string = pop(operator_stack);
            while (strcmp(string, "(") != 0) {
                postfix_array[index] = string;
                index++;
                string = pop(operator_stack);
            }
        }
        // Обработка случая, если функция - операнд (переменная или число)
        else if (is_operand(*token)) {
            postfix_array[index] = *token;
            index++;
        }
        // Обработка случая, если у нас токен - функция
        else if (is_function(*token)) {
            push(operator_stack, *token);
        }
        // Обработка случая оператора
        else if (is_operator(*token)) {
            if (operator_stack->count == 0 ||
                strcmp(traverse_stack(operator_stack->top, operator_stack->count), "(") == 0) {
                push(operator_stack, *token);
            } else {
                // 1 : приоритет вершины стека больше либо равен --> вытолкнуть на выход пока это правда или
                // стек не станет пустым 2 : приоритет вершины стека меньше --> добавить в стек По сути
                // сначала вытаскиваем из стека все что имеет больший приоритет чем токен, после чего
                // добавляем в стек токен
                while (operator_stack->count != 0 &&
                       cmp_priority(traverse_stack(operator_stack->top, operator_stack->count), *token) ==
                           1 &&
                       strcmp(traverse_stack(operator_stack->top, operator_stack->count), "(") != 0) {
                    postfix_array[index] = pop(operator_stack);
                    index++;
                }
                push(operator_stack, *token);
            }
        }
    }
    while (operator_stack->count != 0) {
        postfix_array[index] = pop(operator_stack);
        index++;
    }
    *num_tokens -= brackets_count;
    destroy(operator_stack);
    return postfix_array;
}

int is_operand(char *token) {
    char *end_p;
    strtod(token, &end_p);
    return (*end_p == '\0' || strcmp(token, "x") == 0);
}

int is_function(char *token) {
    int flag = 0;
    char *functions[] = {"sin", "cos", "tan", "ctg", "sqrt", "ln"};
    for (int i = 0; i < 6; i++) {
        if (strcmp(token, functions[i]) == 0) flag = 1;
    }
    return flag;
}

int is_operator(char *token) {
    int flag = 0;
    char *operators[] = {"+", "-", "*", "/"};
    for (int i = 0; i < 4; i++) {
        if (strcmp(token, operators[i]) == 0) flag = 1;
    }
    return flag;
}

char *traverse_stack(NODE *top, int count) {
    char *str = NULL;
    if (count != 0) {
        for (int i = 0; i < count - 1; i++) {
            top = top->next;
        }
        str = top->str;
    }
    return str;
}

int cmp_priority(char *top_stack, char *token) {
    int top_stack_priority = get_priority(top_stack);
    int token_priority = get_priority(token);
    return top_stack_priority >= token_priority ? 1 : 2;
}

int get_priority(char *token) {
    int priority;
    if (is_operator(token) && (strcmp(token, "+") == 0 || strcmp(token, "-") == 0))
        priority = 1;
    else if (is_operator(token) && (strcmp(token, "*") == 0 || strcmp(token, "/") == 0))
        priority = 2;
    else
        priority = 3;
    return priority;
}

double compute_polish(char **tokens, int num_tokens, double x) {
    double result[num_tokens];
    int top = -1;

    for (int i = 0; i < num_tokens; i++) {
        if (strcmp(tokens[i], "+") == 0) {
            double operand2 = result[top--];
            double operand1 = result[top--];
            result[++top] = operand1 + operand2;
        } else if (strcmp(tokens[i], "-") == 0) {
            double operand2 = result[top--];
            double operand1 = result[top--];
            result[++top] = operand1 - operand2;
        } else if (strcmp(tokens[i], "*") == 0) {
            double operand2 = result[top--];
            double operand1 = result[top--];
            result[++top] = operand1 * operand2;
        } else if (strcmp(tokens[i], "/") == 0) {
            double operand2 = result[top--];
            double operand1 = result[top--];
            result[++top] = operand1 / operand2;
        } else if (strcmp(tokens[i], "sin") == 0) {
            double operand = result[top--];
            result[++top] = sin(operand);
        } else if (strcmp(tokens[i], "cos") == 0) {
            double operand = result[top--];
            result[++top] = cos(operand);
        } else if (strcmp(tokens[i], "tan") == 0) {
            double operand = result[top--];
            result[++top] = tan(operand);
        } else if (strcmp(tokens[i], "ctg") == 0) {
            double operand = result[top--];
            result[++top] = 1.0 / tan(operand);
        } else if (strcmp(tokens[i], "sqrt") == 0) {
            double operand = result[top--];
            result[++top] = sqrt(operand);
        } else if (strcmp(tokens[i], "ln") == 0) {
            double operand = result[top--];
            result[++top] = log(operand);
        } else if (strcmp(tokens[i], "x") == 0) {
            result[++top] = x;
        } else {
            result[++top] = atof(tokens[i]);
        }
    }
    return result[top];
}