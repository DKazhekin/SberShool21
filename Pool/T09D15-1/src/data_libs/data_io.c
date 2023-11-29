#include "data_io.h"

#include <stdio.h>
#include <stdlib.h>

int input(double **data, int *n) {
    char buffer;
    int error_code = 1;
    if (scanf("%d%c", n, &buffer) == 2 && buffer <= 32) {
        *data = malloc(*n * sizeof(double));
        for (double *p = *data; p - *data < *n; p++) {
            if (!(scanf("%lf%c", p, &buffer) == 2 && buffer <= 32)) {
                error_code = 0;
            }
        }
    } else {
        error_code = 0;
    }
    return error_code;
}
void output(double *data, int n) {
    for (double *p = data; p - data < n; p++) {
        if (p - data < n - 1) {
            printf("%.2lf ", *p);
        } else {
            printf("%.2lf", *p);
        }
    }
}