#ifndef POLISH_NOTATION_MODULE_H
#define POLISH_NOTATION_MODULE_H
#include <math.h>
#include <string.h>

#include "stack_module.h"

double compute_polish(char **tokens, int num_tokens, double x);
char **infix_to_postfix(char **tokens, int *num_tokens);
int is_function(char *token);
int is_operand(char *token);
int is_operator(char *token);
char *traverse_stack(NODE *top, int count);
int cmp_priority(char *top_stack, char *token);
int get_priority(char *token);

#endif