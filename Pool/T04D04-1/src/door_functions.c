#include "math.h"
#include "stdio.h"

double function1(double x);
double function2(double x);
double function3(double x);

int main() {
    double right = 3.14159265358979323846, left = -3.14159265358979323846;
    double delta = (right - left) / 41;

    while (left < right - delta) {
        if (isnan(function2(left)) == 1) {
            double res1 = function1(left);
            double res3 = function3(left);
            printf("%.7f | %.7f | - | %.7f\n", left, res1, res3);
        } else {
            double res1 = function1(left);
            double res2 = function2(left);
            double res3 = function3(left);
            printf("%.7f | %.7f | %.7f | %.7f\n", left, res1, res2, res3);
        }
        left += delta;
    }

    if (isnan(function2(right)) == 1) {
        double res1 = function1(right);
        double res3 = function3(right);
        printf("%.7f | %.7f | - | %.7f", right, res1, res3);
    } else {
        double res1 = function1(right);
        double res2 = function2(right);
        double res3 = function3(right);
        printf("%.7f | %.7f | %.7f | %.7f", right, res1, res2, res3);
    }

    return 0;
}

double function1(double x) { return pow(1, 3) / (pow(1, 2) + pow(x, 2)); }

double function2(double x) {
    return sqrt(sqrt(pow(1, 4) + 4 * pow(x, 2) * pow(1, 2)) - pow(x, 2) - pow(1, 2));
}

double function3(double x) { return 1 / pow(x, 2); }
