// C++ in 199 Pages - 1.4 Constants: const and constexpr
// Build: g++ -std=c++17 04_constants.cpp -o constants && ./constants

#include <iostream>

constexpr double kPi = 3.14159265358979;   // known at compile time
constexpr int kDaysPerWeek = 7;

int main() {
    const double taxRate = 0.18;           // fixed once set, cannot change
    double price = 250.0;

    // taxRate = 0.2;   // error: assignment of read-only variable

    double total = price + price * taxRate;
    std::cout << "Price with tax: " << total << "\n";

    double radius = 2.0;
    std::cout << "Circle area: " << kPi * radius * radius << "\n";
    std::cout << "Hours in a week: " << kDaysPerWeek * 24 << "\n";
    return 0;
}
