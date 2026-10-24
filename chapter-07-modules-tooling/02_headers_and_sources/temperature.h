// C++ in 199 Pages - 7.2 Header file: the "menu" of what temperature.cpp offers.
// Build: g++ -std=c++17 main.cpp temperature.cpp -o temps && ./temps
#pragma once

#include <string>

double celsiusToFahrenheit(double c);
double fahrenheitToCelsius(double f);
std::string describe(double celsius);
