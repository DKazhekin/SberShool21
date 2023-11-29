#include <stdio.h>
#include <stdlib.h>

void greeting(int *mode, int *error_code);
int **scan_matrix(int **mat, int *rows, int *columns, int *error_code);
void print_matrix(int **mat, int rows, int columns);
void _sum(int **mat1, int rows1, int columns1, int **mat2, int rows2, int columns2);
int **_prod(int **mat1, int rows1, int columns1, int **mat2, int rows2, int columns2);
int **_transpose(int **mat, int rows, int columns);
void free_memory(int **matrix, int columns);

int main() {
    int mode, rows1, columns1, rows2, columns2, error_code = 1;
    greeting(&mode, &error_code);
    if (error_code) {
        if (mode == 1 || mode == 2) {
            int **matrix1 = NULL;
            int **matrix2 = NULL;
            matrix1 = scan_matrix(matrix1, &rows1, &columns1, &error_code);
            matrix2 = scan_matrix(matrix2, &rows2, &columns2, &error_code);
            if (matrix1 != NULL && matrix2 != NULL && error_code) {
                if (mode == 1) {
                    _sum(matrix1, rows1, columns1, matrix2, rows2, columns2);
                    print_matrix(matrix1, rows1, columns1);
                } else if (mode == 2) {
                    int **result = NULL;
                    result = _prod(matrix1, rows1, columns1, matrix2, rows2, columns2);
                    print_matrix(result, rows1, columns2);
                    free(result);
                }
            } else {
                printf("n/a");
            }
            free(matrix1);
            free(matrix2);
        } else {
            int **matrix = NULL;
            matrix = scan_matrix(matrix, &rows1, &columns1, &error_code);
            if (matrix != NULL && error_code) {
                int **result = NULL;
                result = _transpose(matrix, rows1, columns1);
                print_matrix(result, columns1, rows1);
                free_memory(result, columns1);
            } else {
                printf("n/a");
            }
            free(matrix);
        }
    } else {
        printf("n/a");
    }
}

int **scan_matrix(int **mat, int *rows, int *columns, int *error_code) {
    char buffer1, buffer2, extra;
    scanf("%d%c%d%c", rows, &buffer1, columns, &buffer2);
    if (buffer1 != ' ' || buffer2 >= 32) {
        *error_code = 0;
        return NULL;
    }
    mat = malloc(*rows * *columns * sizeof(int) + *rows * sizeof(int *));
    int *ptr = (int *)(mat + *rows);
    for (int i = 0; i < *rows; i++) {
        mat[i] = (int *)ptr + *columns * i;
    }
    for (int i = 0; i < *rows; i++) {
        for (int j = 0; j < *columns; j++) {
            scanf("%d%c", &mat[i][j], &extra);
            if (j < *columns - 1) {
                if (extra != ' ') {
                    *error_code = 0;
                    return NULL;
                }
            } else {
                if (extra < 32) {
                    *error_code = 1;
                } else {
                    *error_code = 0;
                    return NULL;
                }
            }
        }
    }
    return mat;
}

void greeting(int *mode, int *error_code) {
    printf("Выберите арифметическое действие:\n");
    printf("1. Суммирование двух матриц\n");
    printf("2. Умножение матриц\n");
    printf("3. Транспонирование\n");
    char extra;
    scanf("%d%c", mode, &extra);

    if (extra >= 32 || *mode > 3 || *mode < 0) {
        *error_code = 0;
        return;
    }
}

void print_matrix(int **mat, int rows, int columns) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (j < columns - 1) {
                printf("%d ", mat[i][j]);
            } else {
                printf("%d", mat[i][j]);
            }
        }
        printf("\n");
    }
}

void _sum(int **mat1, int rows1, int columns1, int **mat2, int rows2, int columns2) {
    if (rows1 == rows2 && columns1 == columns2) {
        for (int i = 0; i < rows1; i++) {
            for (int j = 0; j < columns2; j++) {
                mat1[i][j] = mat1[i][j] + mat2[i][j];
            }
        }
    } else {
        printf("n/a");
    }
}

int **_prod(int **mat1, int rows1, int columns1, int **mat2, int rows2, int columns2) {
    if (columns1 == rows2) {
        int **result;
        result = malloc(rows1 * columns2 * sizeof(int) + rows1 * sizeof(int *));
        int *ptr = (int *)(result + rows1);
        for (int i = 0; i < rows1; i++) {
            result[i] = (int *)ptr + columns2 * i;
        }

        for (int i = 0; i < rows1; i++) {
            for (int j = 0; j < columns2; j++) {
                result[i][j] = 0;
                for (int k = 0; k < columns1; k++) {
                    result[i][j] += mat1[i][k] * mat2[k][j];
                }
            }
        }
        return result;
    } else {
        printf("n/a");
        return NULL;
    }
}

int **_transpose(int **mat, int rows, int columns) {
    int **result = malloc(columns * sizeof(int *));

    for (int i = 0; i < columns; i++) {
        result[i] = malloc(rows * sizeof(int));
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            result[j][i] = mat[i][j];
        }
    }
    return result;
}

void free_memory(int **matrix, int columns) {
    for (int i = 0; i < columns; i++) {
        free(matrix[i]);
    }
    free(matrix);
}