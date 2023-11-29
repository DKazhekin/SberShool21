#include <stdio.h>
#include <stdlib.h>
#define COLUMNS 100
#define ROWS 100

void print_greeting_scan_dims(int *mode, int *rows, int *columns, int *error_code);
void scan_matrix_static(int data[][COLUMNS], int rows, int columns, int *error_code);
void scan_dmatrix_one_buffer(int **data, int rows, int columns, int *error_code);
void scan_dmatrix_array_of_pointers(int **data, int rows, int columns, int *error_code);
void scan_dmatrix_ptrs_of_segments(int **ptrs_2_arrays, int *values, int rows, int columns, int *error_code);
void print_matrix_static(int data[][COLUMNS], int rows, int columns);
void print_dmatrix(int **data, int rows, int columns);
void print_ptrs_of_segments(int *values, int rows, int columns);
void free_one_buffer(int **dynamic_data);
void free_array_of_ptrs(int **dynamic_data, int rows);
void free_ptrs_to_segs(int **dynamic_data, int *values);

int main() {
    int mode, rows, columns, error_code = 1;
    print_greeting_scan_dims(&mode, &rows, &columns, &error_code);
    if (error_code) {
        if (mode == 1) {
            int data[ROWS][COLUMNS];
            scan_matrix_static(data, rows, columns, &error_code);
            if (error_code) {
                print_matrix_static(data, rows, columns);
            } else {
                printf("n/a");
            }
        } else if (mode == 2) {
            int **dynamic_data = malloc(rows * columns * sizeof(int) + rows * sizeof(int *));
            scan_dmatrix_one_buffer(dynamic_data, rows, columns, &error_code);
            if (error_code) {
                print_dmatrix(dynamic_data, rows, columns);
                free_one_buffer(dynamic_data);
            } else {
                printf("n/a");
            }
        } else if (mode == 3) {
            int **dynamic_data = malloc(rows * sizeof(int *));
            scan_dmatrix_array_of_pointers(dynamic_data, rows, columns, &error_code);
            if (error_code) {
                print_dmatrix(dynamic_data, rows, columns);
                free_array_of_ptrs(dynamic_data, rows);
            } else {
                printf("n/a");
            }

        } else {
            int **ptrs = malloc(rows * sizeof(int *));
            int *values = malloc(columns * rows * sizeof(int));
            scan_dmatrix_ptrs_of_segments(ptrs, values, rows, columns, &error_code);
            if (error_code) {
                print_ptrs_of_segments(values, rows, columns);
                free_ptrs_to_segs(ptrs, values);
            } else {
                printf("n/a");
            }
        }
    } else {
        printf("n/a");
    }
    return 0;
}

void print_greeting_scan_dims(int *mode, int *rows, int *columns, int *error_code) {
    printf("Выберите способ выделения памяти в программе:\n");
    printf("1. Статический\n");
    printf("2. Динамический - с одним буфером\n");
    printf("3. Динамический - массив указателей на массивы значений строк\n");
    printf("4. Динамический - массив указателей на сегменты массива\n");

    char buffer1, buffer2, extra;
    scanf("%d%c", mode, &extra);

    if (extra >= 32 || *mode > 4 || *mode < 0) {
        *error_code = 0;
        return;
    } else {
        scanf("%d%c%d%c", rows, &buffer1, columns, &buffer2);
        if (buffer1 != ' ' || buffer2 != '\n' || (*mode == 1 && (*rows > 100 || *columns > 100))) {
            *error_code = 0;
            return;
        }
    }
}

void scan_matrix_static(int data[][COLUMNS], int rows, int columns, int *error_code) {
    char buffer;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            scanf("%d%c", &data[i][j], &buffer);
            if (j < columns - 1) {
                if (buffer != ' ') {
                    *error_code = 0;
                    return;
                }
            } else {
                if (buffer < 32) {
                    *error_code = 1;
                } else {
                    *error_code = 0;
                    return;
                }
            }
        }
    }
}

void print_matrix_static(int data[][COLUMNS], int rows, int columns) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (j < columns - 1) {
                printf("%d ", data[i][j]);
            } else {
                printf("%d", data[i][j]);
            }
        }
        if (i < rows - 1) {
            printf("\n");
        }
    }
}

void scan_dmatrix_one_buffer(int **data, int rows, int columns, int *error_code) {
    char buffer;
    int *ptr = (int *)(data + rows);
    for (int i = 0; i < rows; i++) {
        data[i] = (int *)ptr + columns * i;
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            scanf("%d%c", &data[i][j], &buffer);
            if (j < columns - 1) {
                if (buffer != ' ') {
                    *error_code = 0;
                    return;
                }
            } else {
                if (buffer < 32) {
                    *error_code = 1;
                } else {
                    *error_code = 0;
                    return;
                }
            }
        }
    }
}

void scan_dmatrix_array_of_pointers(int **data, int rows, int columns, int *error_code) {
    char buffer;
    for (int i = 0; i < rows; i++) {
        data[i] = malloc(columns * sizeof(int));
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            scanf("%d%c", &data[i][j], &buffer);
            if (j < columns - 1) {
                if (buffer != ' ') {
                    *error_code = 0;
                    return;
                }
            } else {
                if (buffer < 32) {
                    *error_code = 1;
                } else {
                    *error_code = 0;
                    return;
                }
            }
        }
    }
}

void scan_dmatrix_ptrs_of_segments(int **ptrs_2_arrays, int *values, int rows, int columns, int *error_code) {
    char buffer;
    for (int i = 0; i < rows; i++) {
        ptrs_2_arrays[i] = values + i * columns;
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            scanf("%d%c", &ptrs_2_arrays[i][j], &buffer);
            if (j < columns - 1) {
                if (buffer != ' ') {
                    *error_code = 0;
                    return;
                }
            } else {
                if (buffer < 32) {
                    *error_code = 1;
                } else {
                    *error_code = 0;
                    return;
                }
            }
        }
    }
}

void print_dmatrix(int **data, int rows, int columns) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (j < columns - 1) {
                printf("%d ", data[i][j]);
            } else {
                printf("%d", data[i][j]);
            }
        }
        if (i < rows - 1) {
            printf("\n");
        }
    }
}

void free_one_buffer(int **dynamic_data) { free(dynamic_data); }

void free_array_of_ptrs(int **dynamic_data, int rows) {
    for (int i = 0; i < rows; i++) {
        free(dynamic_data[i]);
    }
    free(dynamic_data);
}

void print_ptrs_of_segments(int *values, int rows, int columns) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (j < columns - 1) {
                printf("%d ", values[i * columns + j]);
            } else {
                printf("%d", values[i * columns + j]);
            }
        }
        if (i < rows - 1) {
            printf("\n");
        }
    }
}

void free_ptrs_to_segs(int **dynamic_data, int *values) {
    free(values);
    free(dynamic_data);
}