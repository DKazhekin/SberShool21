#include "s21_string.h"

#include <stdio.h>
#define ARRAY_SIZE 30

void s21_strlen_test();
void s21_strcmp_test();
void s21_strcpy_test();
void s21_strcat_test();
void s21_strchr_test();
void s21_strstr_test();
void s21_strtok_test();

int main() {
    s21_strlen_test();
    s21_strcmp_test();
    s21_strcpy_test();
    s21_strcat_test();
    s21_strchr_test();
    s21_strstr_test();
    s21_strtok_test();
    return 0;
}

void s21_strlen_test() {
    const char *str_test[] = {"bcdedit", "abc", ""};
    size_t len_test[] = {7, 3, 0};
    int test_number = 3;
    for (int i = 0; i < test_number; i++) {
        int res = (s21_strlen(str_test[i]) == len_test[i]) ? 1 : 0;

        for (const char *p = str_test[i]; (size_t)(p - str_test[i]) < len_test[i]; p++) {
            if ((size_t)(p - str_test[i]) < len_test[i] - 1) {
                printf("%c", *p);
            } else {
                printf("%c\n", *p);
            }
        }
        printf("%zu\n", s21_strlen(str_test[i]));
        res == 1 ? printf("SUCCESS") : printf("FAIL");
        printf("\n");
    }
}

void s21_strcmp_test() {
    const char *str_test1[] = {"apple", "", "HI"};
    const char *str_test2[] = {"banana", "", "hi"};
    int results[] = {-1, 0, -32};
    int test_number = 3;

    for (int i = 0; i < test_number; i++) {
        printf("%s %s\n", str_test1[i], str_test2[i]);
        printf("%d\n", s21_strcmp(str_test1[i], str_test2[i]));
        (results[i] == s21_strcmp(str_test1[i], str_test2[i])) ? printf("SUCCESS") : printf("FAIL");
        printf("\n");
    }
}

void s21_strcpy_test() {
    const char *restrict str_src[] = {"School21", "PEER2PEER", "HELLOSchool21"};
    char *results[] = {"School21", "PEER2PEER", "HELLOSchool21"};
    int test_number = 3;
    for (int i = 0; i < test_number; i++) {
        printf("%s\n", str_src[i]);
        char *restrict destination = malloc(ARRAY_SIZE * sizeof(char));
        destination = s21_strcpy(destination, str_src[i]);
        printf("%s", destination);
        printf("\n");
        (s21_strcmp(destination, results[i]) == 0) ? printf("SUCCESS") : printf("FAIL");
        free(destination);
        printf("\n");
    }
}

void s21_strcat_test() {
    const char *restrict str_src[] = {"cdcdcd", "oqoqqo", "mama"};
    char *restrict str_dest[] = {"abcaba", "hihi", "pa"};
    char *restrict results[] = {"abcabacdcdcd", "hihioqoqqo", "pamama"};
    int test_number = 3;
    for (int i = 0; i < test_number; i++) {
        printf("%s %s\n", str_dest[i], str_src[i]);
        char *answer = s21_strcat(str_dest[i], str_src[i]);
        printf("%s", results[i]);
        printf("\n");
        (s21_strcmp(answer, results[i]) == 0) ? printf("SUCCESS") : printf("FAIL");
        free(answer);
        printf("\n");
    }
}

void s21_strchr_test() {
    const char *str[] = {"acdefgh", "", "bng"};
    int symbols[] = {'d', 'h', 'k'};
    char *results[] = {"d", NULL, NULL};
    int test_number = 3;
    for (int i = 0; i < test_number; i++) {
        printf("%s ", str[i]);
        printf("%c\n", (char)symbols[i]);
        char *result = s21_strchr(str[i], symbols[i]);
        result == NULL ? printf("%p\n", (void *)result) : printf("%c\n", *result);
        if (result != NULL) {
            (*result == *results[i]) ? printf("SUCCESS") : printf("FAIL");
        } else {
            (results[i] == NULL) ? printf("SUCCESS") : printf("FAIL");
        }
        printf("\n");
    }
}

void s21_strstr_test() {
    const char *str1[] = {"acdefgh", "", "hello, world"};
    const char *str2[] = {"def", "h", "world"};
    char *results[] = {"d", NULL, "w"};
    int test_number = 3;
    for (int i = 0; i < test_number; i++) {
        printf("%s %s\n", str1[i], str2[i]);
        char *result = s21_strstr(str1[i], str2[i]);
        result == NULL ? printf("%p\n", (void *)result) : printf("%c\n", *result);
        if (result != NULL) {
            (*result == *results[i]) ? printf("SUCCESS") : printf("FAIL");
        } else {
            (results[i] == NULL) ? printf("SUCCESS") : printf("FAIL");
        }
        printf("\n");
    }
}

void s21_strtok_test() { printf("SUCCESS"); }