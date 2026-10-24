// C++ in 199 Pages - 7.2 main.cpp only needs the header, not the source.
// Build: g++ -std=c++17 main.cpp temperature.cpp -o temps && ./temps

#include <iostream>
#include "temperature.h"     // quotes: look in this project's folder first

int main() {
    for (double c : {4.0, 18.0, 29.0, 41.0}) {
        std::cout << c << " C = " << celsiusToFahrenheit(c) << " F, " << describe(c) << "\n";
    }
    std::cout << "98.6 F = " << fahrenheitToCelsius(98.6) << " C\n";
    return 0;
}
