#include <ncurses.h>
#include <stdio.h>
#include <unistd.h>

void field(int rocket_one, int rocket_two, int x_ball, int y_ball, int player_one_score,
           int player_two_score);
void congratulations(int rocket_one, int rocket_two, int x_ball, int y_ball, int player_one_score,
                     int player_two_score);
int check_rocket(int coordinate, char mode);
int state_ball(int state, int x_ball, int y_ball, int rocket_one, int rocket_two);
int move_ball_x(int ball_state);
int move_ball_y(int ball_state);

int main() {
    int rocket_one = 14, rocket_two = 14, x_ball = 40, y_ball = 14, ball_state = 3, ball_speed = 75000,
        player_one_score = 0, player_two_score = 0;
    char input;

    initscr();
    noecho();
    cbreak();
    curs_set(0);
    nodelay(stdscr, TRUE);

    field(rocket_one, rocket_two, x_ball, y_ball, player_one_score, player_two_score);
    input = getch();

    while (input != 'q') {
        if (player_one_score == 21 || player_two_score == 21) {
            congratulations(rocket_one, rocket_two, x_ball, y_ball, player_one_score, player_two_score);
            break;
        }

        usleep(ball_speed);

        if (input == 'a' || input == 'z' || input == 'A' || input == 'Z') {
            rocket_one += ((input == 'a' || input == 'A') && check_rocket(rocket_one, input)) ? -1 : 0;
            rocket_one += ((input == 'z' || input == 'Z') && check_rocket(rocket_one, input)) ? 1 : 0;
        } else if (input == 'k' || input == 'm' || input == 'K' || input == 'M') {
            rocket_two += ((input == 'k' || input == 'K') && check_rocket(rocket_two, input)) ? -1 : 0;
            rocket_two += ((input == 'm' || input == 'M') && check_rocket(rocket_two, input)) ? 1 : 0;
        }

        if (x_ball > 80 || x_ball < 1) {
            rocket_one = rocket_two = 14;
            y_ball = 13;
            player_one_score += (x_ball > 80) ? 1 : 0;
            player_two_score += (x_ball <= 1) ? 1 : 0;
            x_ball = 40;
            usleep(200000);
        }

        ball_state = state_ball(ball_state, x_ball, y_ball, rocket_one, rocket_two);
        x_ball += move_ball_x(ball_state);
        y_ball += move_ball_y(ball_state);

        field(rocket_one, rocket_two, x_ball, y_ball, player_one_score, player_two_score);
        input = getch();
    }
    endwin();
    return 0;
}

void field(int rocket_one, int rocket_two, int x_ball, int y_ball, int player_one_score,
           int player_two_score) {
    mvprintw(0, 0, "                                   %.2d       %.2d\n", player_one_score,
             player_two_score);
    for (int y = 1; y <= 27; y++) {
        for (int x = 0; x <= 81; x++) {
            if (y == 1 || y == 27) {
                mvprintw(y, x, "#");
            } else if (x == x_ball && y == y_ball) {
                mvprintw(y, x, "*");
            } else if ((x == 0 || x == 81) && y <= 26) {
                mvprintw(y, x, ".");
            } else {
                if (x == 1) {
                    if (y == rocket_one + 1 || y == rocket_one || y == rocket_one - 1) {
                        mvprintw(y, x, "|");
                    } else {
                        mvprintw(y, x, " ");
                    }
                } else if (x == 80) {
                    if (y == rocket_two + 1 || y == rocket_two || y == rocket_two - 1) {
                        mvprintw(y, x, "|");
                    } else {
                        mvprintw(y, x, " ");
                    }
                } else {
                    mvprintw(y, x, " ");
                }
            }
        }
    }
    refresh();
}

int check_rocket(int coordinate, char mode) {
    if (mode == 'a' || mode == 'k') {
        if (coordinate - 1 >= 3) {
            return 1;
        }
        return 0;
    } else {
        if (coordinate + 1 <= 25) {
            return 1;
        } else {
            return 0;
        }
    }
}

int state_ball(int state, int x_ball, int y_ball, int rocket_one, int rocket_two) {
    if (y_ball == 2) {
        if (state == 4) {
            return 6;
        } else {
            return 3;
        }
    } else if (y_ball == 26) {
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

void congratulations(int rocket_one, int rocket_two, int x_ball, int y_ball, int player_one_score,
                     int player_two_score) {
    if (player_one_score == 21) {
        field(rocket_one, rocket_two, x_ball, y_ball, player_one_score, player_two_score);
        mvprintw(10, 25, "CONGRATULATIONS, PLAYER 1 WON !");
        refresh();
        usleep(5000000);
    } else if (player_two_score == 21) {
        field(rocket_one, rocket_two, x_ball, y_ball, player_one_score, player_two_score);
        mvprintw(10, 25, "CONGRATULATIONS, PLAYER 2 WON !");
        refresh();
        usleep(5000000);
    }
}
