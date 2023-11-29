#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double **input(double **matrix, int *n, int *m);
double det_calculating(double **mat, int n);
void mat_sub(double **mat, int cur_row, int n);
void swap(double **mat, int a, int b);

int main() {
    int n = 0, m = 0;
    double **matrix = NULL, det;
    matrix = input(matrix, &n, &m);
    if (matrix != NULL) {
        det = det_calculating(matrix, n);
        free(matrix);
        printf("%.6lf", det);
    } else {
        printf("n/a");
    }
    return 0;
}

double **input(double **matrix, int *n, int *m) {
    char buffer1, buffer2, extra;
    scanf("%d%c%d%c", n, &buffer1, m, &buffer2);
    if (buffer1 != ' ' || *n == 0 || *m == 0 || buffer2 >= 32 || *n != *m) {
        return NULL;
    }
    matrix = malloc(*n * *m * sizeof(double) + *n * sizeof(double *));
    double *ptr = (double *)(matrix + *n);
    for (int i = 0; i < *n; i++) {
        matrix[i] = ptr + *m * i;
    }
    for (int i = 0; i < *n; i++) {
        for (int j = 0; j < *m; j++) {
            scanf("%lf%c", &matrix[i][j], &extra);
            if (j < *m - 1) {
                if (extra != ' ') {
                    return NULL;
                }
            } else {
                if (extra >= 32) {
                    return NULL;
                }
            }
        }
    }
    return matrix;
}

double det_calculating(double **mat, int n) {
    double det = 1;
    int count_zeros = 0;
    for (int i = 0; i < n - 1; i++) {
        // Если элемент на главной диагонали равен нулю, то необходимо избавиться от этого, заменив данную
        // строку на более нижнюю
        if (mat[i][i] == 0) {
            for (int j = i + 1; j < n; j++) {
                if (mat[j][i] != 0) {
                    swap(mat, i, j);
                    count_zeros++;
                    break;
                }
            }
        } else {
            mat_sub(mat, i, n);
        }
    }
    for (int i = 0; i < n; i++) {
        det *= mat[i][i];
    }
    if (count_zeros % 2 == 1) {
        det *= -1;
    }
    if (det == 0) {
        det = fabs(det);
    }
    return det;
}

void swap(double **mat, int a, int b) {
    double *tmp = mat[a];
    mat[a] = mat[b];
    mat[b] = tmp;
}

void mat_sub(double **mat, int curr_row, int n) {
    double array[n];
    for (int i = 0; i < n; i++) {
        array[i] = mat[curr_row][i];
    }

    for (int i = curr_row + 1; i < n; i++) {
        double multi = mat[i][curr_row] / mat[curr_row][curr_row];
        for (int j = 0; j < n; j++) {
            mat[i][j] -= array[j] * multi;
        }
    }
}