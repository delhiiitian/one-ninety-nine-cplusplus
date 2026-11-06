// C++ in 199 Pages - 7.9 The library's public header.
#pragma once

#include <vector>

namespace stats {
double mean(const std::vector<double>& values);
double median(std::vector<double> values);     // by value: we sort a copy
double standardDeviation(const std::vector<double>& values);
}  // namespace stats
