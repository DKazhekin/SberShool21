#include <math.h>
#include <stdio.h>

#define NMAX 30

void input(int *data, int *n, int *error_code);
double mean(const int *data, int n);
double variance(int *data, int n);
int check(int number, double mean_v, double variance_v);

int main() {
    int n, data[NMAX];
    int error_code = 1;

    input(data, &n, &error_code);
    if (error_code) {
        double mean_v, variance_v;
        mean_v = mean(data, n);
        variance_v = variance(data, n);
        for (int i = 0; i < n; i++) {
            if (check(data[i], mean_v, variance_v)) {
                printf("%d", data[i]);
                return 0;
            }
        }
        printf("0");
    } else {
        printf("n/a");
    }

    return 0;
}

void input(int *data, int *n, int *error_code) {
    char extra;
    scanf("%d%c", n, &extra);

    if (*n > NMAX || *n <= 0 || extra - '0' >= 32) {
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

double mean(const int *data, int n) {
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += data[i];
    }
    return sum / (double)n;
}

double variance(int *data, int n) {
    double sum = 0.0, M;
    double count = 0.0;

    M = mean(data, n);

    for (int *p = data; p - data < n; p++) {
        sum += (*p - M) * (*p - M);
        count++;
    }
    return (double)(sum / count);
}

int check(int number, double mean_v, double variance_v) {
    return (number % 2 == 0 && number >= mean_v && number <= mean_v + 3 * sqrt(variance_v) && number != 0);
}