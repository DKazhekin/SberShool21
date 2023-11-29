#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define COLS 80
#define ROWS 25
#define H_DEPTH 4

void scan(int **mat);
void matrixInit(int ***matr, int rows, int cols);
void drawField(int **matrix);
void cellLife(int **matrix, int *isRunning);
int countNeighbors(int **matrix, int x, int y);
void controls(double *delay, int *isRunning);
int cmp(int ***dest);
int ***create3DMatrix(int rows, int cols, int depth);
void copy2DTo3D(int **src, int ***dest, int depth);
int checkCyclic(int ***history, int iteration);
void free_3Dmatrix(int ***matrix);

int main() {
    int isRunning = 1;
    int iterations = 0;
    double delay = 1;

    int **cellsStatus = NULL;
    matrixInit(&cellsStatus, ROWS, COLS);
    int ***history = create3DMatrix(ROWS, COLS, H_DEPTH);
    scan(cellsStatus);

    // Пасхалочка :)
    if (!freopen("/dev/tty", "r", stdin)) {
        printf("n/a");
    }

    initscr();
    keypad(stdscr, TRUE);
    noecho();
    nodelay(stdscr, TRUE);
    curs_set(FALSE);

    while (isRunning) {
        controls(&delay, &isRunning);
        drawField(cellsStatus);
        usleep(delay * 100000);
        mvprintw(0, 32, "Game speed: %lf", delay);
        cellLife(cellsStatus, &isRunning);
        copy2DTo3D(cellsStatus, history, iterations % 4);
        // Cycle check
        if (iterations > 2) {
            if (!checkCyclic(history, iterations)) {
                mvprintw(13, 26, "Cycle detected!");
                refresh();
                isRunning = 0;
            }
        }
        iterations++;
    }
    mvprintw(14, 27, "Game Over!");
    refresh();
    sleep(5);
    free(cellsStatus);
    free_3Dmatrix(history);
    endwin();
    return 0;
}
void controls(double *delay, int *isRunning) {
    int ch = getch();
    if (ch == 'q' || ch == 'Q') {
        *isRunning = 0;
    } else if (ch == 'f' || ch == 'F') {
        if (*delay > 1)
            *delay -= 0.1;
        else
            *delay = 1;
    } else if (ch == 's' || ch == 'S') {
        if (*delay < 10)
            *delay += 0.1;
        else
            *delay = 10;
    }
}

void matrixInit(int ***matr, int rows, int cols) {
    int **matrix = malloc(rows * cols * sizeof(int) + rows * sizeof(int *));
    if (matrix != NULL) {
        int *pointers = (int *)(matrix + rows);
        for (int i = 0; i < rows; i++) matrix[i] = pointers + cols * i;
    }
    *matr = matrix;
}

void drawField(int **matrix) {
    clear();
    for (int i = 0; i < COLS + 1; i++) {
        mvprintw(1, i, "#");
    }
    for (int i = 0; i < ROWS; i++) {
        mvprintw(i + 2, 0, "#");
        for (int j = 0; j < COLS; j++) {
            mvprintw(i + 2, j + 1, "%c", matrix[i][j] ? '@' : ' ');
        }
        mvprintw(i + 2, COLS, "#");
    }
    for (int i = 0; i < COLS + 1; i++) {
        mvprintw(27, i, "#");
    }
}

void cellLife(int **matrix, int *isRunning) {
    int **newMatrix = NULL;
    matrixInit(&newMatrix, ROWS, COLS);

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            int liveNeightbors = countNeighbors(matrix, i, j);
            if (matrix[i][j] == 1)
                newMatrix[i][j] = (liveNeightbors == 2 || liveNeightbors == 3) ? 1 : 0;
            else
                newMatrix[i][j] = (liveNeightbors == 3) ? 1 : 0;
        }
    }
    int sameCellsCount = 0;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (matrix[i][j] == newMatrix[i][j]) sameCellsCount++;
            matrix[i][j] = newMatrix[i][j];
        }
    }

    if (sameCellsCount == ROWS * COLS) *isRunning = 0;

    free(newMatrix);
    newMatrix = NULL;
}

int countNeighbors(int **matrix, int x, int y) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int row = (x + i + ROWS) % ROWS;
            int col = (y + j + COLS) % COLS;
            if (!(i == 0 && j == 0) && matrix[row][col] == 1) count++;
        }
    }
    return count;
}

void scan(int **mat) {
    int x, y, flag = 1;
    while (flag) {
        if (scanf("%d %d", &y, &x) == 2) {
            mat[y][x] = 1;
        } else {
            // Если ввод не удался, проверяем, является ли причиной конец ввода ('q' или 'Q')
            int ch = getchar();
            if (ch == 'q' || ch == 'Q' || ch == EOF) {
                flag = 0;
            }
        }
    }
}

int checkCyclic(int ***history, int iteration) {
    int result = 1;
    for (int i = 0; i < iteration; i++) {
        if (cmp(history) == 1) {
            result = 0;
        }
    }
    return result;
}

void copy2DTo3D(int **src, int ***dest, int depth) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            dest[i][j][depth] = src[i][j];
        }
    }
}

int ***create3DMatrix(int rows, int cols, int depth) {
    int ***matrix = (int ***)malloc(rows * sizeof(int **));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int **)malloc(cols * sizeof(int *));
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = (int *)malloc(depth * sizeof(int));
        }
    }
    return matrix;
}

int cmp(int ***dest) {
    int flag1 = 1, flag2 = 1;
    for (int j = 0; j < ROWS; j++) {
        for (int m = 0; m < COLS; m++) {
            if (dest[j][m][0] != dest[j][m][2]) {
                flag1 = 0;
            }
            if (dest[j][m][1] != dest[j][m][3]) {
                flag2 = 0;
            }
        }
    }
    return flag1 * flag2;
}

void free_3Dmatrix(int ***matrix) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            free(matrix[i][j]);
        }
        free(matrix[i]);
    }
    free(matrix);
}