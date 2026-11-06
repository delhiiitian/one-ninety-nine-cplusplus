// C++ in 199 Pages - 7.9 The library's implementation, compiled once into libstats.a.
#include "stats.h"

#include <algorithm>
#include <cmath>
#include <numeric>

namespace stats {

double mean(const std::vector<double>& values) {
    if (values.empty()) return 0.0;
    return std::accumulate(values.begin(), values.end(), 0.0) / values.size();
}

double median(std::vector<double> values) {
    if (values.empty()) return 0.0;
    std::sort(values.begin(), values.end());
    std::size_t mid = values.size() / 2;
    return values.size() % 2 == 1 ? values[mid] : (values[mid - 1] + values[mid]) / 2.0;
}

double standardDeviation(const std::vector<double>& values) {
    if (values.size() < 2) return 0.0;
    double m = mean(values);
    double sumSquares = 0.0;
    for (double v : values) sumSquares += (v - m) * (v - m);
    return std::sqrt(sumSquares / (values.size() - 1));
}

}  // namespace stats
