#include "data_stat.h"

double _max(double *data, int n) {
    double MAX = *data;
    for (double *p = data; p - data < n; p++) {
        if (*p > MAX) {
            MAX = *p;
        }
    }
    return MAX;
}
double _min(double *data, int n) {
    double MIN = *data;
    for (double *p = data; p - data < n; p++) {
        if (*p < MIN) {
            MIN = *p;
        }
    }
    return MIN;
}
double _mean(double *data, int n) {
    double SUM = 0;
    for (double *p = data; p - data < n; p++) {
        SUM += *p;
    }
    return SUM / (double)n;
}
double _variance(double *data, int n) {
    double MEAN = _mean(data, n);
    double SUM = 0;
    for (double *p = data; p - data < n; p++) {
        SUM += (*p - MEAN) * (*p - MEAN);
    }
    return SUM / (double)n;
}