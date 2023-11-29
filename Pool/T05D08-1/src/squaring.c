#include <stdio.h>
#define NMAX 10

void input(int *a, int *n, int *error_code);
void output(int *a, int n);
void squaring(int *a, int n);

int main() {
    int n, error_code = 1, data[NMAX];

    input(data, &n, &error_code);
    if (error_code) {
        squaring(data, n);
        output(data, n);
    } else {
        printf("n/a");
    }

    return 0;
}

void input(int *data, int *n, int *error_code) {
    char extra;

    scanf("%d%c", n, &extra);
    if (*n > 10 || *n <= 0 || extra - '0' >= 32) {
        *error_code = 0;
        return;
    }
    for (int *p = data; p - data < *n; p++) {
        scanf("%d%c", p, &extra);
        if (extra == ' ' || (extra - '0' < 32 && p - data == *n - 1 && extra != '.')) {
            *error_code = 1;
        } else {
            *error_code = 0;
            break;
        }
    }
}

void output(int *data, int n) {
    for (int *p = data; p - data < n - 1; p++) {
        printf("%d ", *p);
    }
    printf("%d", data[n - 1]);
}

void squaring(int *data, int n) {
    for (int *p = data; p - data < n; p++) {
        *p = (*p) * (*p);
    }
}