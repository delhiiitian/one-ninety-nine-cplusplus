// C++ in 199 Pages - Project 7: Geometry Library
// shapes.h - simple shapes and the functions that measure them.
#pragma once

#include <vector>

#include "geometry/point.h"

namespace geo {

constexpr double kPi = 3.14159265358979323846;

struct Circle {
    Point center;
    double radius = 0.0;
};

struct Rectangle {
    Point bottomLeft;
    double width = 0.0;
    double height = 0.0;
};

struct Triangle {
    Point a, b, c;
};

// A polygon is any closed shape given by its corners in order.
struct Polygon {
    std::vector<Point> vertices;
};

// Overloaded: one name per idea, one version per shape.
double area(const Circle& c);
double area(const Rectangle& r);
double area(const Triangle& t);
double area(const Polygon& p);

double perimeter(const Circle& c);
double perimeter(const Rectangle& r);
double perimeter(const Triangle& t);
double perimeter(const Polygon& p);

bool contains(const Rectangle& r, const Point& p);
bool contains(const Circle& c, const Point& p);
Rectangle boundingBox(const Polygon& p);

}  // namespace geo
