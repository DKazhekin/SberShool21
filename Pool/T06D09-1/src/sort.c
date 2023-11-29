#include <stdio.h>

#define NMAX 10
#define MAXKEY 2000000

int min(int *data, int n);

void input(int *data, int *error_code, int *is_negative);

void output(int *data);

void counting_sort(int *data);

int main() {
    int data[NMAX], error_code = 1, is_negative = 0;
    input(data, &error_code, &is_negative);
    if (error_code) {
        counting_sort(data);
        output(data);
    } else {
        printf("n/a");
    }
    return 0;
}

void input(int *data, int *error_code, int *is_negative) {
    char extra;
    for (int *p = data; p - data < NMAX; p++) {
        scanf("%d%c", p, &extra);
        if (*p < 0) {
            *is_negative = 1;
        }
        if (p - data < NMAX - 1) {
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

void output(int *data) {
    for (int i = 0; i < NMAX; i++) {
        printf("%d ", data[i]);
    }
}

void counting_sort(int *data) {
    int minimum = min(data, 10);
    if (minimum < 0) {
        for (int *p = data; p - data < NMAX; p++) {
            *p -= minimum;
        }
    }
    int count[MAXKEY + 1] = {0};
    for (int *p = data; p - data < NMAX; p++) {
        count[*p]++;
    }
    for (int i = 1; i <= MAXKEY; ++i) {
        count[i] += count[i - 1];
    }
    int sorted_data[NMAX];
    for (int i = NMAX - 1; i >= 0; --i) {
        int index = --count[*(data + i)];
        sorted_data[index] = data[i];
    }
    if (minimum < 0) {
        for (int *p = sorted_data; p - sorted_data < NMAX; p++) {
            *p += minimum;
        }
    }
    for (int i = 0; i < NMAX; i++) {
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