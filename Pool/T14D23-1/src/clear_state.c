#include <stdio.h>
#include <string.h>
#define FILE_NAME_PATH 500
#define DATES_LEN 22

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

void input(char *date, char *file_name);
void clean(char *date, char *file_name);
void strip(char *file_name);
void sort_binary(FILE *file, long int size);
int cmp_func(FILE *file, long int index);
DATA get_by_id(FILE *file, long int id);
void set_by_id(FILE *file, long int id, DATA *data);
void print_binary(FILE *file, long int size);

int main() {
    char file_name[FILE_NAME_PATH];
    char date[DATES_LEN];
    input(date, file_name);
    clean(date, file_name);
    return 0;
}

void input(char *date, char *file_name) {
    // Считывание пути до файла и его обработка
    fgets(file_name, FILE_NAME_PATH, stdin);
    strip(file_name);
    // Считывание даты для поиска
    fgets(date, DATES_LEN, stdin);
    strip(date);
}

void strip(char *file_name) {
    int index = strlen(file_name) - 1;
    if (file_name[index] == '\n' && index + 1 > 0) file_name[index] = '\0';
}

void clean(char *date, char *file_name) {
    int deleted = 0;
    //  Определяем размер файла в байтах и закрываем его
    FILE *file = fopen(file_name, "rb");
    fseek(file, 0, SEEK_END);
    long int byte_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    long int count_structs = byte_size / sizeof(DATA);

    // Парсим дату
    int year_from, month_from, day_from, year_to, month_to, day_to;
    if (sscanf(date, "%d.%d.%d %d.%d.%d", &day_from, &month_from, &year_from, &day_to, &month_to, &year_to) ==
        6) {
        if (count_structs > 0) {
            sort_binary(file, count_structs);
            FILE *new_file = fopen("tmp.bin", "wb");
            int flag = 1;
            for (int i = 0; i < count_structs; i++) {
                DATA buffer = get_by_id(file, i);
                if (day_from == buffer.day && month_from == buffer.month && year_from == buffer.year)
                    flag = 0;
                if (flag) {
                    fwrite(&buffer, sizeof(DATA), 1, new_file);
                } else {
                    deleted++;
                }
                if (day_to == buffer.day && month_to == buffer.month && year_to == buffer.year) flag = 1;
            }
            fclose(new_file);
        } else {
            printf("n/a");
            fclose(file);
            return;
        }
    } else {
        printf("n/a");
        fclose(file);
        return;
    }
    fclose(file);

    remove(file_name);
    rename("tmp.bin", file_name);

    FILE *files = fopen(file_name, "rb");
    print_binary(files, count_structs - deleted);
    fclose(files);
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
void set_by_id(FILE *file, long int id, DATA *data) {
    fseek(file, id * sizeof(DATA), SEEK_SET);
    fwrite(data, sizeof(DATA), 1, file);
}

DATA get_by_id(FILE *file, long int id) {
    DATA data;
    fseek(file, id * sizeof(DATA), SEEK_SET);
    fread(&data, sizeof(DATA), 1, file);
    return data;
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