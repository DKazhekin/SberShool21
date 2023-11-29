#include <stdio.h>
#include <stdlib.h>

#define MAXKEY 2000000

int min(int *data, int n);
void input(int **data, int *length, int *error_code, int *is_negative);
void output(int *data, int length);
void counting_sort(int *data, int length);

int main() {
    int error_code = 1, is_negative = 0, length;
    int *data = NULL;
    input(&data, &length, &error_code, &is_negative);
    if (error_code) {
        counting_sort(data, length);
        output(data, length);
        free(data);
    } else {
        printf("n/a");
        free(data);
    }
    return 0;
}
void input(int **data, int *length, int *error_code, int *is_negative) {
    char extra;
    scanf("%d%c", length, &extra);
    if (*length > 10 || *length <= 0 || extra >= 32) {
        *error_code = 0;
        return;
    }
    *data = malloc(*length * sizeof(int));
    for (int *p = *data; p - *data < *length; p++) {
        scanf("%d%c", p, &extra);
        if (*p < 0) {
            *is_negative = 1;
        }
        if (p - *data < *length - 1) {
            if (extra != ' ') {
                *error_code = 0;
                return;
            }
        } else {
            if (extra < 32) {
                *error_code = 1;
            } else {
                *error_code = 0;
            }
        }
    }
}

void output(int *data, int length) {
    for (int i = 0; i < length; i++) {
        printf("%d ", data[i]);
    }
}

void counting_sort(int *data, int length) {
    int minimum = min(data, 10);
    if (minimum < 0) {
        for (int *p = data; p - data < length; p++) {
            *p -= minimum;
        }
    }
    int count[MAXKEY + 1] = {0};
    for (int *p = data; p - data < length; p++) {
        count[*p]++;
    }
    for (int i = 1; i <= MAXKEY; ++i) {
        count[i] += count[i - 1];
    }
    int sorted_data[length];
    for (int i = length - 1; i >= 0; --i) {
        int index = --count[*(data + i)];
        sorted_data[index] = data[i];
    }
    if (minimum < 0) {
        for (int *p = sorted_data; p - sorted_data < length; p++) {
            *p += minimum;
        }
    }
    for (int i = 0; i < length; i++) {
        data[i] = sorted_data[i];
    }
}

int min(int *data, int n) {
    int minimum = *data;
    for (int *p = data; p - data < n; p++) {
        if (*p < minimum) {
            minimum = *p;
        }
    }
    return minimum;
}
