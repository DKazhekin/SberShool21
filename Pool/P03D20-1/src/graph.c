#include "drawing.h"
#include "expression_parser.h"
#include "polish_notation_module.h"

char *get_string(int *len);

int main() {
    printf("Enter an expression: ");
    int len;
    char *expression = get_string(&len);
    char **tokens = malloc(len * sizeof(char *));
    int num_tokens = 0;
    //Разбор строки выражения expression и получение списка лексем tokens.
    if (parsing(expression, tokens, &num_tokens) == 0) {
        //Перевод в польскую нотацию.
        char **polish_tokens = infix_to_postfix(tokens, &num_tokens);
        draw_graph(polish_tokens, num_tokens);  //Вычисление и отрисовка графика в терминале.
        free(polish_tokens);
        for (int i = 0; i < len; i++) {
            free(tokens[i]);
        }
    } else {
        printf("Invalid input\n");
    }
    free(expression);
    free(tokens);
    return 0;
}

char *get_string(int *len) {
    *len = 0;
    int flag = 1;
    int capacity = 1;
    int minus_count = 0;
    char *s = malloc(sizeof(char));
    char c = getchar();
    while (c != '\n' && flag) {
        if (c == '-') {
            minus_count++;
        }
        s[(*len)++] = c;
        // если реальный размер больше размера контейнера, то увеличим его размер
        if (*len >= capacity) {
            capacity *= 2;
            char *new_s = realloc(s, capacity * sizeof(char));
            if (new_s == NULL) {
                free(s);
                s = NULL;
                flag = 0;
            }
            if (flag) s = new_s;
        }
        if (flag) c = getchar();
    }
    if (flag && s != NULL) {
        *len += minus_count;
        s[*len] = '\0';  // завершаем строку символом конца строки
    }
    return s;
}
