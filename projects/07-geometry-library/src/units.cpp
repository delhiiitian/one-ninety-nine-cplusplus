#include "geometry/units.h"

namespace geo::units {

double toSquareFeet(double squareMetres) { return squareMetres * kSqFeetPerSqMetre; }
double toGuntha(double squareMetres) { return toSquareFeet(squareMetres) / kSqFeetPerGuntha; }

}  // namespace geo::units
