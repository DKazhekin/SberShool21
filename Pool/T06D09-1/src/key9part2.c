#include <stdio.h>
#define LEN 100

void sum(const int *number1, int length1, const int *number2, int length2, int *_sum);
void sub(const int *number1, int length1, const int *number2, int length2, int *_sub);
void input(int *data, int *length, int *error_code);
void output(int *data, int length);
void sum_refactor(int *data, int length, int *_sum_length);
void sub_refactor(int *data, int length, int *_sub_length);
void shiftRight(int *data, int length);
void shiftLeft(int *data, int length);
int check(const int *number1, const int *number2, int length1);

int main() {
    int number1[LEN], length1, length2, _sum_length, _sub_length, error_code = 1;

    // Считываем первый массив
    input(number1, &length1, &error_code);

    if (error_code) {
        int number2[LEN];
        // Считываем второй массив
        input(number2, &length2, &error_code);

        // Делаем две проверки на большинство первого числа над вторым
        if (length2 > length1) {
            error_code = 0;
        } else if (length1 == length2) {
            if (!check(number1, number2, length1)) error_code = 0;
        }
        if (error_code) {
            int _sum[LEN], _sub[LEN];
            sum(number1, length1, number2, length2, _sum);
            sum_refactor(_sum, length1, &_sum_length);

            sub(number1, length1, number2, length2, _sub);
            sub_refactor(_sub, length1, &_sub_length);

            output(_sum, _sum_length);
            printf("\n");
            output(_sub, _sub_length);
        } else {
            printf("n/a");
        }
    } else {
        printf("n/a");
    }
    return 0;
}

void sum(const int *number1, int length1, const int *number2, int length2, int *_sum) {
    int index_decrement = 1;
    for (int i = length2 - 1; i >= 0; i--) {
        _sum[length1 - index_decrement] = number2[i] + number1[length1 - index_decrement];
        index_decrement++;
    }
    for (int i = length1 - index_decrement; i >= 0; i--) {
        _sum[length1 - index_decrement] = number1[length1 - index_decrement];
        index_decrement++;
    }
}

void sum_refactor(int *data, int length, int *_sum_length) {
    *_sum_length = length;
    for (int i = length - 1; i > 0; i--) {
        if (data[i] > 9) {
            int whole_part = data[i] / 10;
            int remains = data[i] % 10;
            data[i - 1] += whole_part;
            data[i] = remains;
        }
    }
    while (data[0] > 9) {
        shiftRight(data, LEN);
        data[0] = data[1] / 10;
        data[1] = data[1] % 10;
        *_sum_length += 1;
    }
}

void sub(const int *number1, int length1, const int *number2, int length2, int *_sub) {
    int index_decrement = 1;
    for (int i = length2 - 1; i >= 0; i--) {
        _sub[length1 - index_decrement] = number1[length1 - index_decrement] - number2[i];
        index_decrement++;
    }
    for (int i = length1 - index_decrement; i >= 0; i--) {
        _sub[length1 - index_decrement] = number1[length1 - index_decrement];
        index_decrement++;
    }
}

void sub_refactor(int *data, int length, int *_sub_length) {
    *_sub_length = length;
    for (int i = length - 1; i > 0; i--) {
        if (data[i] < 0) {
            data[i - 1] -= 1;
            data[i] = data[i] + 10;
        }
    }
    for (int i = 0; i < length; i++) {
        if (data[i] == 0) {
            *_sub_length -= 1;
        } else {
            for (int j = 0; j < length - *_sub_length; j++) {
                shiftLeft(data, LEN);
            }
            return;
        }
    }
}

void input(int *data, int *length, int *error_code) {
    char extra = ' ';
    int count = 0, init = 0;
    int *p = data, buffer;

    while (extra >= 32) {
        scanf("%d%c", &buffer, &extra);
        if (extra == ' ' || extra == '\n') {
            if (buffer == 0 && !init) {
            } else {
                *p = buffer;
                p++;
                count++;
                init = 1;
            }
        } else {
            *error_code = 0;
            return;
        }
    }
    *length = count;
}

void output(int *data, int length) {
    for (int i = 0; i < length - 1; i++) {
        printf("%d ", data[i]);
    }
    printf("%d", data[length - 1]);
}

void shiftRight(int *data, int length) {
    int lastValue = data[length - 1];
    for (int i = length - 1; i > 0; i--) {
        data[i] = data[i - 1];
    }
    data[0] = lastValue;
}

void shiftLeft(int *data, int length) {
    int firstValue = data[0];
    for (int i = 0; i < length - 1; i++) {
        data[i] = data[i + 1];
    }
    data[length - 1] = firstValue;
}

int check(const int *number1, const int *number2, int length1) {
    for (int i = 0; i < length1; i++) {
        if (number1[i] == number2[i]) {
        } else if (number1[i] > number2[i]) {
            return 1;
        } else {
            return 0;
        }
    }
    return -1;
}
