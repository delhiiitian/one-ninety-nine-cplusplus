// C++ in 199 Pages - Project 7: Plot Calculator
// A small app built on top of the geometry library.
//
// Input: a plot name, the number of corners, the corners as "x y" in metres
// (in order around the boundary), then the fencing price per metre.

#include <iomanip>
#include <iostream>
#include <string>

#include "geometry/shapes.h"
#include "geometry/units.h"

int main() {
    std::string name;
    int corners = 0;
    if (!(std::cin >> name >> corners) || corners < 3) {
        std::cerr << "Expected: <name> <corners> then the corner coordinates\n";
        return 1;
    }

    geo::Polygon plot;
    for (int i = 0; i < corners; ++i) {
        geo::Point p;
        std::cin >> p.x >> p.y;
        plot.vertices.push_back(p);
    }
    double fencePricePerMetre = 0.0;
    std::cin >> fencePricePerMetre;

    double areaM2 = geo::area(plot);
    double fenceM = geo::perimeter(plot);
    geo::Rectangle box = geo::boundingBox(plot);

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Plot: " << name << " (" << corners << " corners)\n";
    std::cout << "  Area:        " << areaM2 << " sq m = "
              << geo::units::toSquareFeet(areaM2) << " sq ft = "
              << geo::units::toGuntha(areaM2) << " guntha\n";
    std::cout << "  Boundary:    " << fenceM << " m\n";
    std::cout << "  Fence cost:  " << fenceM * fencePricePerMetre << "\n";
    std::cout << "  Fits inside: " << box.width << " m x " << box.height << " m\n";
    std::cout << "  Uses " << 100.0 * areaM2 / geo::area(box) << "% of that rectangle\n";
    return 0;
}
