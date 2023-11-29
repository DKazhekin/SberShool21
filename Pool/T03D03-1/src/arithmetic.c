#include <stdio.h>

int sum(int a, int b);
int prod(int a, int b);
int difference(int a, int b);
int div(int a, int b);

int main() {
    int buffer, s, pr, df, dv;
    int a = 0, tmp, space_counter = 0, minus_counter = 0, flag = 0;
    int f_minus = 0;
    int s_minus = 0;
    while (1) {
        buffer = getchar();
        if ((buffer >= '0' && buffer <= '9') || buffer == ' ' || buffer == '\n' || buffer == '-') {
            if (space_counter > 1 || minus_counter > 2) {
                printf("n/a");
                return 0;
            }
            if (buffer == '\n') {
                if (space_counter == 0 || flag == 0) {
                    printf("n/a");
                    return 0;
                }
                if (s_minus == 1) {
                    a = a * -1;
                }
                if (a != 0) {
                    s = sum(tmp, a);
                    pr = prod(tmp, a);
                    df = difference(tmp, a);
                    dv = div(tmp, a);
                    printf("%d %d %d %d", s, df, pr, dv);
                } else {
                    s = sum(tmp, a);
                    pr = prod(tmp, a);
                    df = difference(tmp, a);
                    printf("%d %d %d n/a", s, df, pr);
                }
                return 0;
            } else if (buffer == ' ') {
                space_counter++;
                tmp = a;
                a = 0;
                if (f_minus == 1) {
                    tmp = tmp * -1;
                }
            } else if (buffer == '-') {
                if (space_counter == 1) {
                    s_minus = 1;
                } else {
                    f_minus = 1;
                }
            } else {
                flag = 1;
                int t = buffer - '0';
                a = a * 10 + t;
            }
        } else {
            printf("n/a");
            return 0;
        }
    }
}
int sum(int a, int b) { return a + b; }

int prod(int a, int b) { return a * b; }

int difference(int a, int b) { return a - b; }

int div(int a, int b) { return a / b; }
