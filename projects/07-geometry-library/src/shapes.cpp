#include "geometry/shapes.h"

#include <algorithm>
#include <cmath>
#include <stdexcept>

namespace geo {

double area(const Circle& c) { return kPi * c.radius * c.radius; }
double area(const Rectangle& r) { return r.width * r.height; }

double area(const Triangle& t) {
    // Half the absolute cross product of two sides.
    return std::abs((t.b.x - t.a.x) * (t.c.y - t.a.y) - (t.c.x - t.a.x) * (t.b.y - t.a.y)) / 2.0;
}

// The shoelace formula: works for any simple polygon, corners in order.
double area(const Polygon& p) {
    const auto& v = p.vertices;
    if (v.size() < 3) {
        throw std::invalid_argument("a polygon needs at least 3 vertices");
    }
    double twiceArea = 0.0;
    for (std::size_t i = 0; i < v.size(); ++i) {
        const Point& current = v[i];
        const Point& next = v[(i + 1) % v.size()];   // wraps back to the first
        twiceArea += current.x * next.y - next.x * current.y;
    }
    return std::abs(twiceArea) / 2.0;
}

double perimeter(const Circle& c) { return 2.0 * kPi * c.radius; }
double perimeter(const Rectangle& r) { return 2.0 * (r.width + r.height); }

double perimeter(const Triangle& t) {
    return distance(t.a, t.b) + distance(t.b, t.c) + distance(t.c, t.a);
}

double perimeter(const Polygon& p) {
    const auto& v = p.vertices;
    double total = 0.0;
    for (std::size_t i = 0; i < v.size(); ++i) {
        total += distance(v[i], v[(i + 1) % v.size()]);
    }
    return total;
}

bool contains(const Rectangle& r, const Point& p) {
    return p.x >= r.bottomLeft.x && p.x <= r.bottomLeft.x + r.width &&
           p.y >= r.bottomLeft.y && p.y <= r.bottomLeft.y + r.height;
}

bool contains(const Circle& c, const Point& p) {
    return distance(c.center, p) <= c.radius;
}

Rectangle boundingBox(const Polygon& p) {
    if (p.vertices.empty()) {
        throw std::invalid_argument("empty polygon has no bounding box");
    }
    auto [minX, maxX] = std::minmax_element(p.vertices.begin(), p.vertices.end(),
                                            [](const Point& a, const Point& b) { return a.x < b.x; });
    auto [minY, maxY] = std::minmax_element(p.vertices.begin(), p.vertices.end(),
                                            [](const Point& a, const Point& b) { return a.y < b.y; });
    return {{minX->x, minY->y}, maxX->x - minX->x, maxY->y - minY->y};
}

}  // namespace geo
