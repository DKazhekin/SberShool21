#include "stdio.h"

int fibonacci(int position);

int main() {
    int a;
    scanf("%d", &a);
    if (getc(stdin) == '\n') {
        if (a < 0) {
            printf("n/a");
        } else {
            printf("%d", fibonacci(a));
        }
    } else {
        printf("n/a");
    }
}

int fibonacci(int position) {
    if (position == 0) {
        return 0;
    } else if (position == 1) {
        return 1;
    } else {
        return fibonacci(position - 2) + fibonacci(position - 1);
    }
}
