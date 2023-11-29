#include <stdio.h>

int check(double x, double y);
double power(double base, int exponent);

int main() {
    int buffer, flag = 0;
    int x1 = 0, x2 = 0, space_counter = 0, zero_counter = 0, minus_counter = 0, dot_counter = 0, dot = 0;
    int f_minus = 0, s_minus = 0;
    double result1, result2;
    int legit;
    while (1) {
        buffer = getchar();
        if ((buffer >= '0' && buffer <= '9') || buffer == ' ' || buffer == '\n' || buffer == '-' ||
            buffer == '.') {
            if (space_counter > 1 || minus_counter > 2 || dot_counter > 2) {
                printf("n/a");
                return 0;
            }
            if (buffer == '\n') {
                if (flag == 0) {
                    printf("n/a");
                    return 0;
                }
                if (space_counter == 0) {
                    printf("n/a");
                    return 0;
                }
                if (dot == 0) {
                    x2 = x1;
                    x1 = 0;
                }
                result2 = x2 + (double)x1 / power(10, zero_counter);
                if (s_minus == 1) {
                    result2 = result2 * -1;
                }
                legit = check(result1, result2);
                if (legit == 1) {
                    printf("GOTCHA");
                } else {
                    printf("MISS");
                }
                return 0;
            } else if (buffer == ' ') {
                space_counter++;
                if (dot == 0) {
                    x2 = x1;
                    x1 = 0;
                }
                result1 = x2 + (double)x1 / power(10, zero_counter);
                zero_counter = 0;
                if (f_minus == 1) {
                    result1 = result1 * -1;
                }
                dot = 0;
                x1 = 0, x2 = 0;
            } else if (buffer == '-') {
                if (space_counter == 1) {
                    s_minus = 1;
                } else {
                    f_minus = 1;
                }
            } else if (buffer == '.') {
                dot = 1;
                x2 = x1;
                x1 = 0;
            } else {
                flag = 1;
                int t = buffer - '0';
                x1 = x1 * 10 + t;
                if (dot) {
                    zero_counter++;
                }
            }
        } else {
            printf("n/a");
            return 0;
        }
    }
}

int check(double x, double y) {
    double res = x * x + y * y;

    if (res < 25) {
        return 1;
    } else {
        return 0;
    }
}

double power(double base, int exponent) {
    double result = 1.0;

    if (exponent >= 0) {
        for (int i = 0; i < exponent; i++) {
            result *= base;
        }
    } else {
        for (int i = 0; i > exponent; i--) {
            result /= base;
        }
    }

    return result;
}
