#include <stdio.h>

int max(int a, int b);

int main() {
    int buffer, result, flag = 0;
    int a = 0, tmp, space_counter = 0, minus_counter = 0;
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
                if (flag == 0) {
                    printf("n/a");
                    return 0;
                }
                if (s_minus == 1) {
                    a = a * -1;
                }
                if (space_counter == 0) {
                    printf("n/a");
                    return 0;
                }
                result = max(a, tmp);
                printf("%d", result);

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

int max(int a, int b) {
    if (a > b) {
        return a;
    } else if (a < b) {
        return b;
    } else {
        return a;
    }
}
