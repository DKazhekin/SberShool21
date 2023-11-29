#include "stdio.h"
#define CODE 0
#define DECODE 1

void code();
void decode();
int isASCII(unsigned char ch);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("n/a");
        return 0;
    }
    if ((*argv[1] - '0' == DECODE)) {
        decode();
    } else if (*argv[1] - '0' == CODE) {
        code();
    }
    return 0;
}

void decode() {
    int decimal_code;
    int initialize = 0;
    char buffer1, buffer2, buffer3, extra;
    int hex_digit, hex_number = 0;
    while (1) {
        buffer1 = getc(stdin);
        // Первый символ кодового слова должен начинаться строго с цифры
        if (buffer1 >= '0' && buffer1 <= '9') {
            // Составляем код
            hex_digit = buffer1 - '0';
            hex_number = hex_number * 16 + hex_digit;

            initialize = 1;
            // Второй символ кодового слова должен быть либо цифрой, либо заглавной латинской буквой от A до F
            buffer2 = getc(stdin);
            if ((buffer2 >= '0' && buffer2 <= '9') || (buffer2 >= 'A' && buffer2 <= 'F')) {
                if (buffer2 >= '0' && buffer2 <= '9') {
                    hex_digit = buffer2 - '0';
                } else {
                    hex_digit = buffer2 - 'A' + 10;
                }

                hex_number = hex_number * 16 + hex_digit;

                // Проверка на третий символ: если это не пробел или конец строки то ошибка и пропускам опять
                // слово
                buffer3 = getc(stdin);
                if (buffer3 == ' ') {
                    decimal_code = hex_number;
                    printf("%c", (char)decimal_code);
                    printf(" ");
                } else if (buffer3 == '\n') {
                    decimal_code = hex_number;
                    printf("%c", (char)decimal_code);
                    return;
                } else {
                    // Сбрасываем накопленный код
                    hex_number = 0;

                    printf("n/a");
                    while (1) {
                        extra = getc(stdin);
                        if (extra == '\n') {
                            return;
                        } else if (extra == ' ') {
                            printf(" ");
                            break;
                        }
                    }
                }

            }
            // Иначе пропускаем все что стоит после до пробела или конца строки и выводим ошибку (*)
            else {
                // Сбрасываем накопленный код
                hex_number = 0;

                printf("n/a");
                while (1) {
                    extra = getc(stdin);
                    if (extra == '\n') {
                        return;
                    } else if (extra == ' ') {
                        printf(" ");
                        break;
                    }
                }
            }
        } else {
            // Если ввели сразу ENTER, то выходим и пишем ошибку
            if (buffer1 == '\n' && !initialize) {
                printf("n/a");
                break;
            }

            // !!! Возможно лишнее
            // Если конец ввода, то нужно просто выйти из программы
            else if (buffer1 == '\n' && initialize) {
                break;
            }

            // Если объект начинается с "плохого" символа, то нужно поставить метку n/a и пропустить все
            // символы после до пробела или /n (*)
            else {
                initialize = 1;
                printf("n/a");
                while (1) {
                    extra = getc(stdin);
                    if (extra == '\n') {
                        return;
                    } else if (extra == ' ') {
                        printf(" ");
                        break;
                    }
                }
            }
        }
    }
}

void code() {
    int initialize = 0;
    char buffer1, buffer2, extra;
    while (1) {
        buffer1 = getc(stdin);
        // Если символ принадлежит ASCII таблице, то продолжаем
        if (isASCII((unsigned char)buffer1)) {
            initialize = 1;
            buffer2 = getc(stdin);
            if (buffer2 == ' ') {
                printf("%X ", buffer1);
            } else if (buffer2 == '\n') {
                printf("%X", buffer1);
                return;
            } else {
                printf("n/a");
                while (1) {
                    extra = getc(stdin);
                    if (extra == '\n') {
                        return;
                    } else if (extra == ' ') {
                        printf(" ");
                        break;
                    }
                }
            }
        }
        // Если нет, то
        else {
            // Если ввели сразу ENTER, то выходим и пишем ошибку
            if (buffer1 == '\n' && !initialize) {
                printf("n/a");
                break;
            }

            // !!! Возможно лишнее
            // Если конец ввода, то нужно просто выйти из программы
            else if (buffer1 == '\n' && initialize) {
                break;
            }

            // Если объект начинается с "плохого" символа, то нужно поставить метку n/a и пропустить все
            // символы после до пробела или /n (*)
            else {
                initialize = 1;
                printf("n/a");
                while (1) {
                    extra = getc(stdin);
                    if (extra == '\n') {
                        return;
                    } else if (extra == ' ') {
                        printf(" ");
                        break;
                    }
                }
            }
        }
    }
}

int isASCII(unsigned char ch) { return ch <= 127; }
