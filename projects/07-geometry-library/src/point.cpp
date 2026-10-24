#include "geometry/point.h"

#include <cmath>

namespace geo {

double distance(const Point& a, const Point& b) {
    return std::hypot(b.x - a.x, b.y - a.y);
}

Point midpoint(const Point& a, const Point& b) {
    return {(a.x + b.x) / 2.0, (a.y + b.y) / 2.0};
}

bool nearlyEqual(double a, double b, double tolerance) {
    return std::abs(a - b) <= tolerance;
}

}  // namespace geo
