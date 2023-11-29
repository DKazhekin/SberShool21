#include <stdio.h>
#include <string.h>
#define FILE_NAME_PATH 500
#define DATE_LEN 11

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
void search(char *date, char *file_name);
void strip(char *file_name);
DATA get_by_id(FILE *file, long int id);

int main() {
    char file_name[FILE_NAME_PATH];
    char date[DATE_LEN];
    input(date, file_name);
    search(date, file_name);
    return 0;
}

void input(char *date, char *file_name) {
    // Считывание пути до файла и его обработка
    fgets(file_name, FILE_NAME_PATH, stdin);
    strip(file_name);
    // Считывание даты для поиска
    fgets(date, DATE_LEN, stdin);
    strip(date);
}

void strip(char *file_name) {
    int index = strlen(file_name) - 1;
    if (file_name[index] == '\n' && index + 1 > 0) file_name[index] = '\0';
}

void search(char *date, char *file_name) {
    //  Определяем размер файла в байтах и закрываем его
    FILE *file = fopen(file_name, "rb+");
    fseek(file, 0, SEEK_END);
    long int byte_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    long int count_structs = byte_size / sizeof(DATA);

    // Парсим дату
    int year, month, day;
    if (sscanf(date, "%d.%d.%d", &day, &month, &year) == 3) {
        if (count_structs > 0) {
            for (long int i = 0; i < count_structs; i++) {
                DATA buffer = get_by_id(file, i);
                if (day == buffer.day && month == buffer.month && year == buffer.year) {
                    printf("%d", buffer.code);
                    return;
                }
            }
            printf("n/a");
        } else {
            printf("n/a");
        }
    } else {
        printf("n/a");
    }
    fclose(file);
}

DATA get_by_id(FILE *file, long int id) {
    DATA data;
    fseek(file, id * sizeof(DATA), SEEK_SET);
    fread(&data, sizeof(DATA), 1, file);
    return data;
}