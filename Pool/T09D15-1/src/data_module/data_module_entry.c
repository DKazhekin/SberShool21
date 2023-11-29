#include <stdio.h>
#include <stdlib.h>

#include "../data_libs/data_io.h"
#include "data_process.h"

int main() {
    double *data = NULL;
    int n;

    if (input(&data, &n)) {
        if (normalization(data, n))
            output(data, n);
        else
            printf("ERROR");
        free(data);
    } else {
        printf("ERROR");
    }
}
