#include <stdio.h>
#include <string.h>
#define FILE_NAME_PATH 500

typedef struct data {
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
    int status;
    int code;
} DATA;

int input(int *mode, char *file_name);
void strip(char *file_name);
void action(int mode, char *file_name);
void print_binary(FILE *file, long int size);
DATA get_by_id(FILE *file, long int id);
void set_by_id(FILE *file, long int id, DATA *data);
void sort_binary(FILE *file, long int size);
int cmp_func(FILE *file, long int index);
void add_2_binary(FILE *file, long int *size);
DATA get_note(void);

int main() {
    char file_name[FILE_NAME_PATH];
    int mode;
    if (input(&mode, file_name)) {
        action(mode, file_name);
    } else {
        printf("n/a");
    }
    return 0;
}

int input(int *mode, char *file_name) {
    char extra;
    int flag = 1;
    // Считывание пути до файла и его обработка
    fgets(file_name, FILE_NAME_PATH, stdin);
    strip(file_name);
    // Считывание режима работы программы
    scanf("%d", mode);
    extra = getc(stdin);
    // Обработка корректности ввода
    if (!(extra < 32 && *mode >= 0 && *mode <= 2)) flag = 0;
    return flag;
}

void strip(char *file_name) {
    int index = strlen(file_name) - 1;
    if (file_name[index] == '\n' && index + 1 > 0) file_name[index] = '\0';
}

void action(int mode, char *file_name) {
    //  Определяем размер файла в байтах и закрываем его
    FILE *file = fopen(file_name, "rb+");
    fseek(file, 0, SEEK_END);
    long int byte_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    long int count_structs = byte_size / sizeof(DATA);

    if (count_structs > 0) {
        // Выполняем действие
        if (mode == 0) {
            print_binary(file, count_structs);
        } else if (mode == 1) {
            sort_binary(file, count_structs);
            print_binary(file, count_structs);
        } else {
            fseek(file, 0, SEEK_END);
            add_2_binary(file, &count_structs);
            fseek(file, 0, SEEK_SET);
            sort_binary(file, count_structs);
            print_binary(file, count_structs);
        }
    } else {
        printf("n/a");
    }
    fclose(file);
}

void print_binary(FILE *file, long int size) {
    // Выводим результат
    DATA buffer;
    for (long int i = 0; i < size; i++) {
        buffer = get_by_id(file, i);
        printf("%d %d %d %d %d %d %d %d", buffer.year, buffer.month, buffer.day, buffer.hour, buffer.minute,
               buffer.second, buffer.status, buffer.code);
        if (i < size - 1) printf("\n");
    }
}

void sort_binary(FILE *file, long int size) {
    for (long int i = 0; i < size - 1; i++) {
        for (long int j = 0; j < size - i - 1; j++) {
            if (cmp_func(file, j)) {
                // Меняем местами, если текущий элемент больше следующего
                DATA temp = get_by_id(file, j);
                DATA insert = get_by_id(file, j + 1);
                set_by_id(file, j, &insert);
                set_by_id(file, j + 1, &temp);
            }
        }
    }
}

void add_2_binary(FILE *file, long int *size) {
    DATA note = get_note();
    fwrite(&note, sizeof(DATA), 1, file);
    *size = *size + 1;
}

DATA get_note(void) {
    DATA note;
    scanf("%d %d %d %d %d %d %d %d", &note.year, &note.month, &note.day, &note.hour, &note.minute,
          &note.second, &note.status, &note.code);
    return note;
}

int cmp_func(FILE *file, long int index) {
    DATA a = get_by_id(file, index);
    DATA b = get_by_id(file, index + 1);
    long int years = a.year - b.year;
    if (years > 0) {
        return 1;
    } else if (years == 0) {
        long int months = a.month - b.month;
        if (months > 0) {
            return 1;
        } else if (months == 0) {
            long int days = a.day - b.day;
            if (days > 0) {
                return 1;
            } else if (days == 0) {
                long int hours = a.hour - b.hour;
                if (hours > 0) {
                    return 1;
                } else if (hours == 0) {
                    long int minutes = a.minute - b.minute;
                    if (minutes > 0) {
                        return 1;
                    } else if (minutes == 0) {
                        long int seconds = a.second - b.second;
                        if (seconds > 0) {
                            return 1;
                        }
                    }
                }
            }
        }
    }
    return 0;
}

DATA get_by_id(FILE *file, long int id) {
    DATA data;
    fseek(file, id * sizeof(DATA), SEEK_SET);
    fread(&data, sizeof(DATA), 1, file);
    return data;
}

void set_by_id(FILE *file, long int id, DATA *data) {
    fseek(file, id * sizeof(DATA), SEEK_SET);
    fwrite(data, sizeof(DATA), 1, file);
}