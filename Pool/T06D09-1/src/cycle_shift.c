#include <stdio.h>

#define NMAX 10

void input(int *data, int *length, int *error_code, int *shift);

void output(int *data, int length);

void shift(const int *data, int *data_out, int shift, int length);

int main() {
    int error_code = 0, data[NMAX], length, _shift;

    input(data, &length, &error_code, &_shift);
    if (error_code) {
        int data_out[NMAX];
        shift(data, data_out, _shift, length);
        output(data_out, length);
    } else {
        printf("n/a");
    }
}

void input(int *data, int *length, int *error_code, int *shift) {
    char extra;
    scanf("%d%c", length, &extra);

    if (*length > 10 || *length <= 0 || extra >= 32) {
        *error_code = 0;
        return;
    }
    for (int *p = data; p - data < *length; p++) {
        scanf("%d%c", p, &extra);
        if (p - data < *length - 1) {
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
    scanf("%d%c", shift, &extra);
    if (extra >= 32) {
        *error_code = 0;
        return;
    }
}

void output(int *data, int length) {
    for (int i = 0; i < length; i++) {
        printf("%d ", data[i]);
    }
}

void shift(const int *data, int *data_out, int shift, int length) {
    shift = shift % length;
    if (shift > 0) {
        for (int i = length - 1; i >= 0; i--) {
            if (i < shift) {
                data_out[length + i - shift] = data[i];
            } else {
                data_out[i - shift] = data[i];
            }
        }
    } else {
        for (int i = 0; i < length; i++) {
            if (i - shift > length - 1) {
                data_out[i - shift - (length - 1) - 1] = data[i];
            } else {
                data_out[i - shift] = data[i];
            }
        }
    }
}