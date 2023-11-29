#include <stdio.h>

#define N 15
#define M 13

void transform(int *buf, int **matr, int n, int m);
void make_picture(int **picture, int n, int m);
void reset_picture(int **picture, int n, int m);
void output(int **picture, int n, int m);

int main() {
    // Матрица в явном виде
    int picture_data[N][M];

    // Массив указателей
    int *picture[N];

    // Преобразование матрицы в массив указателей на ее строки
    transform(&picture_data[0][0], picture, N, M);
    make_picture(picture, N, M);
    output(picture, N, M);
}

void make_picture(int **picture, int n, int m) {
    const int frame_w[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    const int frame_h[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    const int tree_trunk[] = {7, 7, 7, 7};
    const int tree_foliage[] = {3, 3, 3, 3};
    const int sun_data[6][5] = {{0, 6, 6, 6, 6}, {0, 0, 6, 6, 6}, {0, 0, 6, 6, 6},
                                {0, 6, 0, 0, 6}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}};

    reset_picture(picture, n, m);

    for (int i = 0; i < N; i++) {
        picture[i][0] = frame_h[i];
        picture[i][M - 1] = frame_h[i];
        picture[i][(M - 1) / 2] = frame_h[i];
    }

    for (int i = 1; i < 5; i++) {
        for (int j = 7; j < 12; j++) {
            picture[i][j] = sun_data[i - 1][j - 7];
        }
    }

    for (int j = 6; j < 10; j++) {
        picture[j - 4][3] = tree_foliage[j - 6];
        picture[j - 4][4] = tree_foliage[j - 6];
        picture[j][3] = tree_trunk[j - 6];
        picture[j][4] = tree_trunk[j - 6];

        picture[10][j - 4] = tree_trunk[j - 6];
        picture[3][j - 4] = tree_foliage[j - 6];
        picture[4][j - 4] = tree_foliage[j - 6];
    }

    for (int i = 2; i < 6; i++) {
        picture[10][i] = tree_trunk[i - 2];
    }

    for (int i = 0; i < M; i++) {
        picture[0][i] = frame_w[i];
        picture[N - 1][i] = frame_w[i];
        picture[(N - 1) / 2][i] = frame_w[i];
    }
}

void reset_picture(int **picture, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            picture[i][j] = 0;
        }
    }
}

void transform(int *buf, int **matr, int n, int m) {
    for (int i = 0; i < n; i++) {
        matr[i] = buf + i * m;
    }
}

void output(int **picture, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (j < m - 1) {
                printf("%d ", picture[i][j]);
            } else {
                printf("%d", picture[i][j]);
            }
        }
        if (i < n - 1) {
            printf("\n");
        }
    }
}