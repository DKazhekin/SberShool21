#include "drawing.h"

void draw_graph(char **tokens, int num_tokens) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            double real_x = (double)x / (WIDTH - 1) * (4 * M_PI);
            double real_y = compute_polish(tokens, num_tokens, real_x);

            if (fabs(real_y - ((double)y / (HEIGHT - 1) * 2 - 1)) < 0.04) {
                printf("*");
            } else {
                printf(".");
            }
        }
        printf("\n");
    }
}