// C++ in 199 Pages - Project 7: unit tests for the geometry library.
#include "geometry/shapes.h"
#include "geometry/units.h"
#include "test_framework.h"

using geo::Point;

void testPoints() {
    CHECK_NEAR(geo::distance({0, 0}, {3, 4}), 5.0);            // the 3-4-5 triangle
    CHECK_NEAR(geo::distance({2, 2}, {2, 2}), 0.0);
    Point m = geo::midpoint({0, 0}, {10, 4});
    CHECK_NEAR(m.x, 5.0);
    CHECK_NEAR(m.y, 2.0);
}

void testSimpleShapes() {
    CHECK_NEAR(geo::area(geo::Rectangle{{0, 0}, 4, 3}), 12.0);
    CHECK_NEAR(geo::perimeter(geo::Rectangle{{0, 0}, 4, 3}), 14.0);
    CHECK_NEAR(geo::area(geo::Circle{{0, 0}, 1}), geo::kPi);
    CHECK_NEAR(geo::perimeter(geo::Circle{{0, 0}, 2}), 4 * geo::kPi);
    geo::Triangle t{{0, 0}, {4, 0}, {0, 3}};
    CHECK_NEAR(geo::area(t), 6.0);
    CHECK_NEAR(geo::perimeter(t), 12.0);
}

void testPolygon() {
    geo::Polygon square{{{0, 0}, {2, 0}, {2, 2}, {0, 2}}};
    CHECK_NEAR(geo::area(square), 4.0);
    CHECK_NEAR(geo::perimeter(square), 8.0);

    geo::Polygon clockwise{{{0, 0}, {0, 2}, {2, 2}, {2, 0}}};   // reverse order
    CHECK_NEAR(geo::area(clockwise), 4.0);

    geo::Polygon lShape{{{0, 0}, {4, 0}, {4, 1}, {1, 1}, {1, 3}, {0, 3}}};
    CHECK_NEAR(geo::area(lShape), 6.0);                          // 4x1 + 1x2

    geo::Rectangle box = geo::boundingBox(lShape);
    CHECK_NEAR(box.width, 4.0);
    CHECK_NEAR(box.height, 3.0);

    CHECK_THROWS(geo::area(geo::Polygon{{{0, 0}, {1, 1}}}));      // too few corners
    CHECK_THROWS(geo::boundingBox(geo::Polygon{}));
}

void testContains() {
    geo::Rectangle room{{0, 0}, 5, 4};
    CHECK(geo::contains(room, {2, 2}));
    CHECK(geo::contains(room, {5, 4}));                          // edge counts as inside
    CHECK(!geo::contains(room, {6, 1}));
    CHECK(geo::contains(geo::Circle{{0, 0}, 2}, {1, 1}));
    CHECK(!geo::contains(geo::Circle{{0, 0}, 1}, {1, 1}));
}

void testUnits() {
    CHECK_NEAR(geo::units::toSquareFeet(1.0), 10.7639);
    CHECK(geo::nearlyEqual(geo::units::toGuntha(101.17), 1.0, 0.001));
}

int main() {
    testPoints();
    testSimpleShapes();
    testPolygon();
    testContains();
    testUnits();
    return testing::summary();
}
