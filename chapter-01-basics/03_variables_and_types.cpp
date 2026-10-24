// C++ in 199 Pages - 1.3 Variables and basic types
// Build: g++ -std=c++17 03_variables_and_types.cpp -o types && ./types

#include <iostream>

int main() {
    int    age         = 29;        // whole numbers
    double heightM     = 1.75;      // numbers with a decimal point
    char   grade       = 'A';       // a single character, single quotes
    bool   isMember    = true;      // true or false
    long long worldPop = 8100000000LL; // very large whole numbers

    std::cout << "Age: " << age << "\n";
    std::cout << "Height (m): " << heightM << "\n";
    std::cout << "Grade: " << grade << "\n";
    std::cout << "Member? " << std::boolalpha << isMember << "\n";
    std::cout << "World population: " << worldPop << "\n";

    // sizeof tells you how many bytes a type uses on this machine
    std::cout << "int uses " << sizeof(int) << " bytes, double uses "
              << sizeof(double) << " bytes\n";

    age = age + 1;                  // variables can change
    std::cout << "Next year: " << age << "\n";
    return 0;
}
