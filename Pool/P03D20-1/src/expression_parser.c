#include "expression_parser.h"

#include <stdio.h>

void process_token(STACK *stack, const char *token) {
    push(stack, strdup(token));  // Push a copy of the token onto the stack
}

void process_operator(STACK *stack, char operator) {
    char token[2];
    token[0] = operator;
    token[1] = '\0';
    process_token(stack, token);
}

void free_tokens(char *tokens[], int num_tokens) {
    for (int i = 0; i < num_tokens; i++) {
        free(tokens[i]);
    }
}

void processTokenRange(STACK *stack, const char *expression, const int *token_start, int i) {
    if (i > *token_start) {
        int token_length = i - *token_start;
        char *token = malloc((token_length + 1) * sizeof(char));
        strncpy(token, expression + *token_start, token_length);
        token[token_length] = '\0';
        process_token(stack, token);
        free(token);
    }
}

void handle_standalone_negative(STACK *stack, int *token_start, const char *expression, int i) {
    processTokenRange(stack, expression, token_start, i);
    char next_char = expression[i + 1];
    if (next_char == 'x' || next_char == '(' || (next_char >= 'a' && next_char <= 'z') ||
        (next_char >= 'A' && next_char <= 'Z')) {
        char *token = (char *)malloc(3 * sizeof(char));
        token[0] = '-';
        token[1] = '1';
        token[2] = '\0';
        push(stack, token);

        char *mul_token = (char *)malloc(2 * sizeof(char));
        mul_token[0] = '*';
        mul_token[1] = '\0';
        push(stack, mul_token);
        *token_start = i + 1;
    } else if (next_char >= '0' && next_char <= '9') {
        int j = i + 1;  // Start from the character after '-'
        while (expression[j] >= '0' && expression[j] <= '9') {
            j++;
        }
        int num_length = j - (i + 1);
        char *num_token = (char *)malloc((num_length + 2) * sizeof(char));
        num_token[0] = '-';
        strncpy(num_token + 1, expression + i + 1, num_length);
        num_token[num_length + 1] = '\0';
        process_token(stack, num_token);
        free(num_token);
        *token_start = j;  // Move token_start past the number
    } else {
        char *token = (char *)malloc(3 * sizeof(char));
        token[0] = '-';
        token[1] = '1';
        token[2] = '\0';
        process_token(stack, token);
        free(token);
        *token_start = i + 1;
    }
}

void handle_minus_after_char(STACK *stack, int *token_start, const char *expression, int i) {
    processTokenRange(stack, expression, token_start, i);

    char next_char = expression[i + 1];
    if (next_char == '-') {
        char *minus_token = (char *)malloc(2 * sizeof(char));
        minus_token[0] = '-';
        minus_token[1] = '\0';
        process_token(stack, minus_token);

        char *mul_token = (char *)malloc(2 * sizeof(char));
        mul_token[0] = '*';
        mul_token[1] = '\0';
        process_token(stack, mul_token);

        *token_start = i + 2;
        free(minus_token);
        free(mul_token);
    } else {
        char *minus_token = (char *)malloc(2 * sizeof(char));
        minus_token[0] = '-';
        minus_token[1] = '\0';
        process_token(stack, minus_token);
        *token_start = i + 1;
        free(minus_token);
    }
}

void parse_operators(STACK *stack, const char *expression, int start, int end, int *token_start) {
    for (int i = start; i < end; i++) {
        if (expression[i] == '(' || expression[i] == ')' || expression[i] == '*' || expression[i] == '/' ||
            expression[i] == '+') {
            if (i > *token_start) {
                int token_length = i - *token_start;
                char *token = (char *)malloc((token_length + 1) * sizeof(char));
                strncpy(token, expression + *token_start, token_length);
                token[token_length] = '\0';
                process_token(stack, token);
                free(token);
            }
            process_operator(stack, expression[i]);
            *token_start = i + 1;
        } else if (expression[i] == '-') {
            if (i == 0 || expression[i - 1] == '(') {
                handle_standalone_negative(stack, token_start, expression, i);
            } else {
                handle_minus_after_char(stack, token_start, expression, i);  // Call the new function
            }
        }
    }
}

int is_valid_operator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')');
}

int is_digit(char c) { return (c >= '0' && c <= '9'); }

int is_valid_function(const char *function_name) {
    return (strcmp(function_name, "sin") == 0 || strcmp(function_name, "cos") == 0 ||
            strcmp(function_name, "tan") == 0 || strcmp(function_name, "ctg") == 0 ||
            strcmp(function_name, "sqrt") == 0 || strcmp(function_name, "ln") == 0);
}

void parse_expression_tokens(STACK *stack, const char *expression, int start, int end) {
    int token_start = start;
    parse_operators(stack, expression, start, end, &token_start);

    if (end > token_start) {
        int token_length = end - token_start;
        char *token = (char *)malloc((token_length + 1) * sizeof(char));
        strncpy(token, expression + token_start, token_length);
        token[token_length] = '\0';
        process_token(stack, token);
        free(token);
    }
}

void validate_token(char *token, int *flag) {
    if (!is_valid_operator(token[0]) && !is_valid_function(token) && token[0] != 'x') {
        if (token[0] != '-' && !is_digit(token[0])) {
            *flag = 1;
        } else {
            *flag = validate_number(token);
        }
    }
}

int validate_number(const char *token) {
    int counter = 0;

    for (int j = 1; j < (int)strlen(token); j++) {
        if (!is_digit(token[j]) && token[j] != '.') {
            return 2;  // Invalid digit or character
        }

        if (token[j] == '.') {
            counter++;
            if (counter > 1) {
                return 3;  // More than one decimal point
            }
        }
    }

    return 0;  // Valid number
}

int validate_tokens(char **tokens, int num_tokens) {
    int flag = 0;
    int open_brac = 0;
    int close_brac = 0;

    for (int i = 0; i < num_tokens && flag == 0; i++) {
        char *token = tokens[i];
        if (i == 0 && (is_valid_operator(token[0]) && token[0] != '(' && token[0] != '-')) {
            flag = 1;
        }

        if (token[0] == '(') {
            open_brac++;
        } else if (token[0] == ')') {
            close_brac++;
        }

        if (token[0] == ' ') {
            flag = 1;
        }

        validate_token(token, &flag);
    }

    if (open_brac != close_brac) flag = 1;

    if (flag != 0) {
        free_tokens(tokens, num_tokens);
    }

    return flag;
}

int parsing(const char *expression, char *tokens[], int *num_tokens) {
    int flag = 0;
    *num_tokens = 0;

    STACK *stack = init(NULL);
    int len = strlen(expression);

    parse_expression_tokens(stack, expression, 0, len);

    *num_tokens = stack->count;
    int original_num_tokens = *num_tokens;

    *num_tokens = original_num_tokens - 1;

    for (int i = *num_tokens - 1; i >= 0; i--) {
        tokens[i] = pop(stack);
    }

    flag = validate_tokens(tokens, *num_tokens);

    destroy(stack);

    return flag;
}
