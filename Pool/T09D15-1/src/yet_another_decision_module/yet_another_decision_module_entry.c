#include <stdio.h>
#include <stdlib.h>

#include "../data_libs/data_io.h"
#include "decision.h"

int main() {
    double *data;
    int n;

    if (input(&data, &n)) {
        if (make_decision(data, n))
            printf("YES");
        else
            printf("NO");
        free(data);
    } else {
        printf("ERROR");
    }
}
