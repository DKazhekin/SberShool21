#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

#include "logger.h"
#define FILE_PATH_LEN 100
#define MESSAGE_LEN 1000
#define FILE_STR_LEN 100
#define FORMAT 1000

void input(int *mode, char *file_name, char *message, int *shift, char *directory, int *error_code);
void action(int mode, char *file_name, char *directory, int shift, char *message, FILE *log);
void strip(char *file_name);
void caesarCipher(char *filename, int shift);
void traverse_dir(char *dir_path, int shift, FILE *log);

int main() {
    int mode, error_code = 1, shift;
    char file_name[FILE_PATH_LEN];
    char directory[FILE_PATH_LEN];
    char message[MESSAGE_LEN];
    FILE *log = log_init("log_file");
    input(&mode, file_name, message, &shift, directory, &error_code);
    while (mode != -1) {
        if (error_code) action(mode, file_name, directory, shift, message, log);
        input(&mode, file_name, message, &shift, directory, &error_code);
    }
    char formatted_string[FORMAT];
    sprintf(formatted_string, "Успешное завершение работы программы\n");
    logcat(log, formatted_string, "INFO");
    log_close(log);
    return 0;
}

void input(int *mode, char *file_name, char *message, int *shift, char *directory, int *error_code) {
    char extra;
    scanf("%d", mode);
    extra = getc(stdin);
    if (extra < 32 && *mode != -1 && (*mode < 1 || *mode > 3)) {
        if (*mode == 1) {
            fgets(file_name, FILE_PATH_LEN, stdin);
            strip(file_name);
        } else if (*mode == 2) {
            fgets(message, MESSAGE_LEN, stdin);
        } else if (*mode == 3) {
            fgets(directory, FILE_PATH_LEN, stdin);
            strip(directory);
            scanf("%d", shift);
            if (getc(stdin) >= 32) {
                printf("n/a\n");
                *error_code = 0;
                fflush(stdin);
            }
        }
        *error_code = 1;
    } else {
        if (*mode != -1) {
            printf("n/a\n");
            *error_code = 0;
            if (extra >= 32) fflush(stdin);
        }
    }
}

void action(int mode, char *file_name, char *directory, int shift, char *message, FILE *log) {
    if (mode == 1) {
        FILE *file = fopen(file_name, "r");
        if (file != NULL) {
            char buffer[FILE_STR_LEN];
            fseek(file, 0, SEEK_END);
            int size = ftell(file);
            // Empty check
            if (size == 0) {
                char formatted_string[FORMAT];
                sprintf(formatted_string, "Безуспешное чтение файла %s, файл пуст\n", file_name);
                logcat(log, formatted_string, "ERROR");
                printf("n/a");
            } else {
                fseek(file, 0, 0);
                while (fgets(buffer, sizeof(buffer), file)) printf("%s", buffer);
                char formatted_string[FORMAT];
                sprintf(formatted_string, "Успешно выполнено чтение файла %s\n", file_name);
                logcat(log, formatted_string, "INFO");
            }
            printf("\n");
        } else {
            char formatted_string[FORMAT];
            sprintf(formatted_string, "Безуспешное чтение файла %s, ошибка в пути до файла\n", file_name);
            logcat(log, formatted_string, "ERROR");
            printf("n/a\n");
        }
        fclose(file);
    } else if (mode == 2) {
        FILE *file = fopen(file_name, "a+");
        if (file != NULL) {
            fprintf(file, "%s", message);
            char buffer[FILE_STR_LEN];
            fseek(file, 0, 0);
            while (fgets(buffer, sizeof(buffer), file)) printf("%s", buffer);
            printf("\n");
            char formatted_string[FORMAT];
            sprintf(formatted_string, "Успешная запись в файл %s\n", file_name);
            logcat(log, formatted_string, "INFO");
        } else {
            char formatted_string[FORMAT];
            sprintf(formatted_string, "Безуспешная запись в файл %s, ошибка в пути до файла\n", file_name);
            logcat(log, formatted_string, "ERROR");
            printf("n/a\n");
        }
        fclose(file);
    } else if (mode == 3) {
        traverse_dir(directory, shift, log);
    }
}

void strip(char *file_name) {
    int index = strlen(file_name) - 1;
    if (file_name[index] == '\n' && index + 1 > 0) file_name[index] = '\0';
}

void caesarCipher(char *filename, int shift) {
    FILE *file = fopen(filename, "r+");

    if (file == NULL) {
        printf("n/a\n");
        return;
    }

    int ch;
    long pos = 0;
    while ((ch = fgetc(file)) != EOF) {
        pos = ftell(file) - 1;
        if (ch >= 'A' && ch <= 'z') {
            if (ch >= 'a' && ch <= 'z') {
                ch = 'a' + (ch - 'a' + shift) % 26;
            } else if (ch >= 'A' && ch <= 'Z') {
                ch = 'A' + (ch - 'A' + shift) % 26;
            }
            fseek(file, pos, SEEK_SET);
            fputc(ch, file);
            fseek(file, pos + 1, SEEK_SET);
        }
    }

    fclose(file);
}

void traverse_dir(char *dir_path, int shift, FILE *log) {
    DIR *dir = opendir(dir_path);
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        char filePath[FORMAT * 2];
        snprintf(filePath, sizeof(filePath), "%s/%s", dir_path, entry->d_name);

        struct stat fileStat;
        if (stat(filePath, &fileStat) == -1) {
            char formatted_string[FORMAT];
            sprintf(formatted_string,
                    "Безуспешная обработка файлов директории %s со сдвигом %d, ошибка в пути до директории\n",
                    dir_path, shift);
            logcat(log, (char *)formatted_string, "ERROR");
            printf("n/a\n");
            continue;
        }

        if (S_ISDIR(fileStat.st_mode)) {
            traverse_dir(filePath, shift, log);
        } else if (S_ISREG(fileStat.st_mode)) {
            if (strstr(entry->d_name, ".c") != NULL) {
                caesarCipher(filePath, shift);
            } else if (strstr(entry->d_name, ".h") != NULL) {
                FILE *file = fopen(filePath, "w");
                fclose(file);
            }
            char formatted_string[FORMAT];
            sprintf(formatted_string, "Успешная обработка файлов директории %s со сдвигом %d\n", dir_path,
                    shift);
            logcat(log, (char *)formatted_string, "INFO");
        }
    }
    closedir(dir);
}