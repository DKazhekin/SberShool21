#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "door_struct.h"

#define DOORS_COUNT 15
#define MAX_ID_SEED 10000

void initialize_doors(DOOR *doors);
void bubbleSort(DOOR *arr, int n);
void output(DOOR *arr, int n);

int main() {
    DOOR doors[DOORS_COUNT];
    initialize_doors(doors);
    bubbleSort(doors, DOORS_COUNT);
    output(doors, DOORS_COUNT);
    return 0;
}

void initialize_doors(DOOR *doors) {
    srand(time(0));

    int seed = rand() % MAX_ID_SEED;
    for (int i = 0; i < DOORS_COUNT; i++) {
        doors[i].id = (i + seed) % DOORS_COUNT;
        doors[i].status = rand() % 2;
    }
}

void bubbleSort(DOOR *arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].id > arr[j + 1].id) {
                // Обмен значениями
                DOOR temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void output(DOOR *arr, int n) {
    for (int i = 0; i < n; i++) {
        arr[i].status = 0;
        printf("%d, %d", arr[i].id, arr[i].status);
        if (i < n - 1) {
            printf("\n");
        }
    }
}