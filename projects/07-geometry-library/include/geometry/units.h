// C++ in 199 Pages - Project 7: Geometry Library
// units.h - conversions used when measuring land in India.
#pragma once

namespace geo::units {

constexpr double kSqFeetPerSqMetre = 10.7639;
constexpr double kSqFeetPerGuntha = 1089.0;   // a guntha is a common land unit

double toSquareFeet(double squareMetres);
double toGuntha(double squareMetres);

}  // namespace geo::units
