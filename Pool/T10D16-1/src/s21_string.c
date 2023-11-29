#include "s21_string.h"
#define ARRAY_LEN 30

size_t s21_strlen(const char *str) {
    const char *p = str;
    while (*p != '\0') {
        p++;
    }
    return (size_t)(p - str);
}

int s21_strcmp(const char *str1, const char *str2) {
    const char *p1 = str1, *p2 = str2;
    while (*p1 != '\0' && *p2 != '\0') {
        if (*p1 != *p2) {
            return *p1 - *p2;
        }
        p1++;
        p2++;
    }
    return 0;
}

char *s21_strcpy(char *restrict dest, const char *restrict src) {
    int count = 0;
    for (int i = 0; src[i] != '\0'; i++) {
        dest[i] = src[i];
        count++;
    }
    dest[count + 1] = '\0';
    return dest;
}

char *s21_strcat(char *restrict dest, const char *restrict src) {
    int i = 0, j = 0;
    char *final = malloc(ARRAY_LEN * sizeof(char));
    while (dest[i] != '\0') {
        final[i] = dest[i];
        i++;
    }
    while (src[j] != '\0') {
        final[i] = src[j];
        i++;
        j++;
    }
    final[i + j] = '\0';
    return final;
}

char *s21_strchr(const char *str, int ch) {
    while (*str != '\0') {
        str++;
        if (*str == ch) {
            return (char *)str;
        }
    }
    return NULL;
}

char *s21_strstr(const char *dest, const char *src) {
    for (const char *p = dest; *p != '\0'; p++) {
        int flag = 1;
        for (int i = 0; *(src + i) != '\0'; i++) {
            if (*(p + i) != *(src + i)) {
                flag = 0;
                break;
            }
        }
        if (flag) return (char *)p;
    }
    return NULL;
}