#include <stdio.h>
#define NMAX 10

void input(int *data, int *n, int *error_code);
void output(int *data, int n);
int max(int *data, int n);
int min(int *data, int n);
double mean(int *data, int n);
double variance(int *data, int n);
void output_result(int max_v, int min_v, double mean_v, double variance_v);

int main() {
    int n, data[NMAX];
    int error_code = 1;

    input(data, &n, &error_code);
    if (error_code) {
        output(data, n);
        output_result(max(data, n), min(data, n), mean(data, n), variance(data, n));
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
    printf("%d\n", data[n - 1]);
}

void output_result(int max_v, int min_v, double mean_v, double variance_v) {
    printf("%d %d %.6lf %.6lf", max_v, min_v, mean_v, variance_v);
}

int max(int *data, int n) {
    int maximum = *data;
    for (int *p = data; p - data < n; p++) {
        if (*p > maximum) {
            maximum = *p;
        }
    }
    return maximum;
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

double mean(int *data, int n) {
    double a = min(data, n);
    double b = max(data, n);
    return (a + b) / 2.0;
}

double variance(int *data, int n) {
    double sum = 0, M;
    double count = 0;

    M = mean(data, n);

    for (int *p = data; p - data < n; p++) {
        sum += (*p - M) * (*p - M);
        count++;
    }
    return sum / count;
}