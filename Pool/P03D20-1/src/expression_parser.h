#ifndef EXPRESSION_PARSER_H
#define EXPRESSION_PARSER_H
#include <stdlib.h>
#include <string.h>

#include "stack_module.h"

void free_tokens(char *tokens[], int num_tokens);
void process_token(STACK *stack, const char *token);
void process_operator(STACK *stack, char operator);
void processTokenRange(STACK *stack, const char *expression, const int *token_start, int i);
void handle_standalone_negative(STACK *stack, int *token_start, const char *expression, int i);
void handle_minus_after_char(STACK *stack, int *token_start, const char *expression, int i);
void parse_operators(STACK *stack, const char *expression, int start, int end, int *token_start);
int is_valid_operator(char c);
int is_digit(char c);
int is_valid_function(const char *function_name);
void parse_expression_tokens(STACK *stack, const char *expression, int start, int end);
int validate_tokens(char **tokens, int num_tokens);
int parsing(const char *expression, char *tokens[], int *num_tokens);
void validate_token(char *token, int *flag);
int validate_number(const char *token);

#endif