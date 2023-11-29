/*------------------------------------
        Здравствуй, человек!
        Чтобы получить ключ
        поработай с комментариями.
-------------------------------------*/

#include <stdio.h>

#define NMAX 10

void input(int *data, int *length, int *error_code);

void output(int *data, int length);

int sum_numbers(int *data, int length);

void find_numbers(int *data, int length, int *length_out, int number, int *numbers);

/*------------------------------------
        Функция получает массив данных
        через stdin.
        Выдает в stdout особую сумму
        и сформированный массив
        специальных элементов
        (выбранных с помощью найденной суммы):
        это и будет частью ключа
-------------------------------------*/
int main() {
    int error_code = 0, data[NMAX], length_data, length_out;

    input(data, &length_data, &error_code);
    if (error_code) {
        int data_out[NMAX];
        find_numbers(data, length_data, &length_out, sum_numbers(data, length_data), data_out);
        printf("%d\n", sum_numbers(data, length_data));
        output(data_out, length_out);
    } else {
        printf("n/a");
    }
}

/*------------------------------------
        Функция должна находить
        сумму четных элементов
        с 0-й позиции.
-------------------------------------*/
int sum_numbers(int *data, int length) {
    int sum = 0;

    for (int i = 0; i < length; i++) {
        if (*(data + i) % 2 == 0 && *(data + i) != 0) {
            sum = sum + data[i];
        }
    }

    return sum;
}

/*------------------------------------
        Функция должна находить
        все элементы, на которые нацело
        делится переданное число и
        записывает их в выходной массив.
-------------------------------------*/
void find_numbers(int *data, int length_data, int *length_out, int number, int *numbers) {
    int i = 0;
    for (int *p = data; p - data < length_data; p++) {
        if (*p != 0 && number % *p == 0) {
            numbers[i] = *p;
            i++;
        }
    }
    *length_out = i;
}

void input(int *data, int *length, int *error_code) {
    char extra;
    scanf("%d%c", length, &extra);

    if (*length > 10 || *length <= 0 || extra >= 32) {
        *error_code = 0;
        return;
    }
    for (int *p = data; p - data < *length; p++) {
        scanf("%d%c", p, &extra);
        if (p - data < *length - 1) {
            if (extra != ' ') {
                *error_code = 0;
                return;
            }
        } else {
            if (extra < 32) {
                *error_code = 1;
            } else {
                *error_code = 0;
            }
        }
    }
}

void output(int *data, int length_out) {
    for (int i = 0; i < length_out; i++) {
        printf("%d ", data[i]);
    }
}