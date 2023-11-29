#include "decision.h"

#include <math.h>

#include "../data_libs/data_stat.h"

int make_decision(double *data, int n) {
    int decision = 1;

    double m = _mean(data, n);
    double sigma = sqrt(_variance(data, n));
    double max_value = _max(data, n);
    double min_value = _min(data, n);

    decision &= (max_value <= m + 3 * sigma) && (min_value >= m - 3 * sigma) && (m >= GOLDEN_RATIO);

    return decision;
}
