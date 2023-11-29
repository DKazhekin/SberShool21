#include <math.h>
#include <stdio.h>

double function(double x);

int main() {
    double glue, result;
    int a = 0, b = 0, minus = 0, buffer, dot = 0, zero_counter = 0;
    while (1) {
        buffer = getchar();
        if ((buffer >= '0' && buffer <= '9') || buffer == '\n' || buffer == '-' || buffer == '.') {
            if (buffer == '\n') {
                glue = b + (double)a / pow(10, zero_counter);
                if (glue == 0) {
                    printf("n/a");
                    return 0;
                }
                if (minus == 1) {
                    glue = glue * -1;
                }
                result = function(glue);
                printf("%.1lf", result);
                return 0;
            } else if (buffer == '-') {
                minus = 1;
            } else if (buffer == '.') {
                dot = 1;
                b = a;
                a = 0;
            } else {
                int t = buffer - '0';
                a = a * 10 + t;
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

double function(double x) {
    double answer = 7e-3 * pow(x, 4) + ((22.8 * pow(x, 1 / 3) - 1e3) * x + 3) / (pow(x, 2) / 2) -
                    x * pow(10 + x, 2 / x) - 1.01;
    return answer;
}
