#include <math.h>
#include <stdio.h>

int input(int *error_code, int *negative);
int gcd(int number);
int divide(int number, int divisor);
int remains(int number, int divisor);
int is_prime(int number);

int main() {
    int in_number, greatest_common_divisor = 1, error_code = 1, negative = 0;
    in_number = input(&error_code, &negative);
    if (in_number == 0) {
        printf("n/a");
        return 0;
    } else if (in_number == 1) {
        printf("n/a");
        return 0;
    }
    if (error_code == 1) {
        if (negative) {
            in_number *= -1;
        }
        greatest_common_divisor = gcd(in_number);
        printf("%d", greatest_common_divisor);
    } else {
        return 0;
    }
}

int input(int *error_code, int *negative) {
    char buffer;
    int m_counter = 0, number = 0, m_flag = 0;

    while (1) {
        buffer = getchar();
        if ((buffer >= '0' && buffer <= '9') || buffer == '\n' || buffer == '-') {
            if (m_counter > 2) {
                printf("n/a");
                *error_code = -1;
                return 0;
            }
            if (buffer == '\n') {
                if (m_flag) {
                    number *= -1;
                }
                return number;

            } else if (buffer == '-') {
                m_flag = 1;
                *negative = 1;
                m_counter++;
            } else {
                int figure = buffer - '0';
                number = number * 10 + figure;
            }
        } else {
            printf("n/a");
            *error_code = -1;
            return 0;
        }
    }
}

int divide(int number, int divisor) {
    int count = 0;
    while (number >= divisor) {
        count++;
        number -= divisor;
    }
    return count;
}

int remains(int number, int divisor) {
    int whole_part = divide(number, divisor);
    return number - (whole_part * divisor);
}

int is_prime(int number) {
    if (number <= 1) {
        return 0;
    }

    if (number == 2) {
        return 1;
    }

    if (remains(number, 2) == 0) {
        return 0;
    }

    int sqrt_num = sqrt(number);
    for (int i = 3; i <= sqrt_num; i += 2) {
        if (remains(number, i) == 0) {
            return 0;
        }
    }

    return 1;
}

int gcd(int number) {
    int greatest_common_divisor = -1;

    for (int i = 2; i <= number; i++) {
        if (remains(number, i) == 0) {
            if (is_prime(i)) {
                if (i > greatest_common_divisor) {
                    greatest_common_divisor = i;
                }
            }
        }
    }
    return greatest_common_divisor;
}
