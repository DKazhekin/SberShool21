#include <stdio.h>
#include <stdlib.h>

#define MAXKEY 2000000

int **sort_vertical(int **matrix, int n, int m);
int **sort_horizontal(int **matrix, int n, int m);
int **input(int **matrix, int *n, int *m);
void counting_sort(int *data, int n);
int min(int *data, int n);
void output(int **matrix, int n, int m);

int main() {
    int **matrix = NULL, **result1 = NULL, **result2 = NULL;
    int n = 0, m = 0;

    matrix = input(matrix, &n, &m);
    if (matrix == NULL) {
        printf("n/a");
    } else {
        result1 = sort_vertical(matrix, n, m);
        output(result1, n, m);
        printf("\n");
        printf("\n");
        result2 = sort_horizontal(matrix, n, m);
        output(result2, n, m);
        free(matrix);
        free(result1);
        free(result2);
    }
    return 0;
}

int **input(int **matrix, int *n, int *m) {
    char buffer1, buffer2, extra;
    scanf("%d%c%d%c", n, &buffer1, m, &buffer2);
    if (buffer1 != ' ' || *n == 0 || *m == 0 || buffer2 >= 32) {
        return NULL;
    }
    matrix = malloc(*n * *m * sizeof(int) + *n * sizeof(int *));
    int *ptr = (int *)(matrix + *n);
    for (int i = 0; i < *n; i++) {
        matrix[i] = (int *)ptr + *m * i;
    }
    for (int i = 0; i < *n; i++) {
        for (int j = 0; j < *m; j++) {
            scanf("%d%c", &matrix[i][j], &extra);
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

int **sort_horizontal(int **matrix, int n, int m) {
    int digits[n * m];
    int direction = 1, row = 0, col = 0;
    int index = 0;

    int **result = malloc(n * m * sizeof(int) + n * sizeof(int *));
    int *ptr = (int *)(matrix + n);
    for (int i = 0; i < n; i++) {
        result[i] = (int *)ptr + m * i;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            digits[index] = matrix[i][j];
            index++;
        }
    }

    counting_sort(digits, n * m);

    for (int i = 0; i < n * m; i++) {
        if (direction == 1) {  // Движение вправо
            if (col == m - 1) {
                result[row][col] = digits[i];
                row++;
                direction = -1;
            } else {
                result[row][col] = digits[i];
                col++;
            }
        } else {  // Движение влево
            if (col == 0) {
                result[row][col] = digits[i];
                row++;
                direction = 1;
            } else {
                result[row][col] = digits[i];
                col--;
            }
        }
    }
    return result;
}

int **sort_vertical(int **matrix, int n, int m) {
    int digits[n * m];
    int index = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            digits[index] = matrix[i][j];
            index++;
        }
    }

    counting_sort(digits, n * m);

    int **result = malloc(n * sizeof(int *));
    int *ptr = (int *)(result + n);
    for (int i = 0; i < n; i++) {
        result[i] = (int *)ptr + m * i;
    }

    int direction = 1;
    int row = 0, col = 0;
    index = 0;

    for (int i = 0; i < n * m; i++) {
        result[row][col] = digits[index];
        index++;

        if (direction == 1) {
            if (row == n - 1) {
                col++;
                direction = -1;
            } else {
                row++;
            }
        } else {
            if (row == 0) {
                col++;
                direction = 1;
            } else {
                row--;
            }
        }
    }

    return result;
}

void counting_sort(int *data, int n) {
    int minimum = min(data, n);
    if (minimum < 0) {
        for (int *p = data; p - data < n; p++) {
            *p -= minimum;
        }
    }
    int count[MAXKEY + 1] = {0};
    for (int *p = data; p - data < n; p++) {
        count[*p]++;
    }
    for (int i = 1; i <= MAXKEY; ++i) {
        count[i] += count[i - 1];
    }
    int sorted_data[n];
    for (int i = n - 1; i >= 0; --i) {
        int index = --count[*(data + i)];
        sorted_data[index] = data[i];
    }
    if (minimum < 0) {
        for (int *p = sorted_data; p - sorted_data < n; p++) {
            *p += minimum;
        }
    }
    for (int i = 0; i < n; i++) {
        data[i] = sorted_data[i];
    }
}

int min(int *data, int n) {
    int minimum = *data;
    for (int *p = data; p - data < n; p++) {
        if (*p < minimum) {
            minimum = *p;
        }
    }
    return minimum;
}

void output(int **mat, int rows, int columns) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (j < columns - 1) {
                printf("%d ", mat[i][j]);
            } else {
                printf("%d", mat[i][j]);
            }
        }
        if (i < rows - 1) {
            printf("\n");
        }
    }
}