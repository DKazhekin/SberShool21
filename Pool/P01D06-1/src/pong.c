#include <stdio.h>

void field(int rocket_one, int rocket_two, int x_ball, int y_ball, int player_one_score,
           int player_two_score);
int check_rocket(int coordinate, char mode);
int state_ball(int state, int x_ball, int y_ball, int rocket_one, int rocket_two);
int move_ball_x(int ball_state);
int move_ball_y(int ball_state);

int main() {
    int rocket_one = 13, rocket_two = 13, x_ball = 40, y_ball = 13, ball_state = 1, player_one_score = 0,
        player_two_score = 0;
    char input, extra;

    field(rocket_one, rocket_two, x_ball, y_ball, player_one_score, player_two_score);
    scanf("%c%c", &input, &extra);

    while (input != 'q') {
        if (player_one_score == 21) {
            printf("PLAYER 1 WINS !");
            break;
        } else if (player_two_score == 21) {
            printf("PLAYER 2 WINS !");
            break;
        }

        if (input == 'a' || input == 'z' || input == 'A' || input == 'Z') {
            rocket_one += ((input == 'a' || input == 'A') && check_rocket(rocket_one, input)) ? -1 : 0;
            rocket_one += ((input == 'z' || input == 'Z') && check_rocket(rocket_one, input)) ? 1 : 0;
        } else if (input == 'k' || input == 'm' || input == 'K' || input == 'M') {
            rocket_two += ((input == 'k' || input == 'K') && check_rocket(rocket_two, input)) ? -1 : 0;
            rocket_two += ((input == 'm' || input == 'M') && check_rocket(rocket_two, input)) ? 1 : 0;
        }

        if (x_ball > 80 || x_ball < 1) {
            rocket_one = 13;
            rocket_two = 13;
            y_ball = 13;
            if (x_ball > 80) {
                player_one_score++;
            } else {
                player_two_score++;
            }
            x_ball = 40;
        }

        ball_state = state_ball(ball_state, x_ball, y_ball, rocket_one, rocket_two);
        x_ball += move_ball_x(ball_state);
        y_ball += move_ball_y(ball_state);
        field(rocket_one, rocket_two, x_ball, y_ball, player_one_score, player_two_score);

        scanf("%c%c", &input, &extra);
    }
    return 0;
}
void field(int rocket_one, int rocket_two, int x_ball, int y_ball, int player_one_score,
           int player_two_score) {
    printf("                                   %.2d       %.2d\n", player_one_score, player_two_score);
    for (int y = 0; y <= 26; y++) {
        for (int x = 0; x <= 81; x++) {
            if (y == 0 || y == 26) {
                printf("#");
            } else if (x == x_ball && y == y_ball) {
                printf("*");
            } else if (x == 0 || x == 81) {
                printf(".");
            } else {
                if (x == 1) {
                    if (y == rocket_one + 1 || y == rocket_one || y == rocket_one - 1) {
                        printf("|");
                    } else {
                        printf(" ");
                    }
                } else if (x == 80) {
                    if (y == rocket_two + 1 || y == rocket_two || y == rocket_two - 1) {
                        printf("|");
                    } else {
                        printf(" ");
                    }
                } else {
                    printf(" ");
                }
            }
        }
        printf("\n");
    }
}

int check_rocket(int coordinate, char mode) {
    if (mode == 'a' || mode == 'k' || mode == 'A' || mode == 'K') {
        if (coordinate - 1 >= 2) {
            return 1;
        }
        return 0;
    } else {
        if (coordinate + 1 <= 24) {
            return 1;
        } else {
            return 0;
        }
    }
}

int state_ball(int state, int x_ball, int y_ball, int rocket_one, int rocket_two) {
    if (y_ball == 1) {
        if (state == 4) {
            return 6;
        } else {
            return 3;
        }
    } else if (y_ball == 25) {
        if (state == 3) {
            return 1;
        } else {
            return 4;
        }
    } else if (x_ball == 79 && y_ball == rocket_two - 1) {
        return 1;
    } else if (x_ball == 79 && y_ball == rocket_two) {
        return 2;
    } else if (x_ball == 79 && y_ball == rocket_two + 1) {
        return 3;
    } else if (x_ball == 2 && y_ball == rocket_one - 1) {
        return 4;
    } else if (x_ball == 2 && y_ball == rocket_one) {
        return 5;
    } else if (x_ball == 2 && y_ball == rocket_one + 1) {
        return 6;
    } else
        return state;
}

int move_ball_x(int ball_state) {
    if (ball_state == 1) {
        return -1;
    } else if (ball_state == 2) {
        return -1;
    } else if (ball_state == 3) {
        return -1;
    } else if (ball_state == 4) {
        return 1;
    } else if (ball_state == 5) {
        return 1;
    } else if (ball_state == 6) {
        return 1;
    } else
        return 0;
}

int move_ball_y(int ball_state) {
    if (ball_state == 1) {
        return -1;
    } else if (ball_state == 2) {
        return 0;
    } else if (ball_state == 3) {
        return 1;
    } else if (ball_state == 4) {
        return -1;
    } else if (ball_state == 5) {
        return 0;
    } else if (ball_state == 6) {
        return 1;
    } else
        return 0;
}
