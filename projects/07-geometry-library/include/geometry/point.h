// C++ in 199 Pages - Project 7: Geometry Library
// point.h - the basic building block: a point on a flat plane.
#pragma once

namespace geo {

struct Point {
    double x = 0.0;
    double y = 0.0;
};

double distance(const Point& a, const Point& b);
Point midpoint(const Point& a, const Point& b);
bool nearlyEqual(double a, double b, double tolerance = 1e-9);

}  // namespace geo
