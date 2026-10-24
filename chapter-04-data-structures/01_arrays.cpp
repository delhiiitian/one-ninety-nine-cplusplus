// C++ in 199 Pages - 4.1 Arrays: C-style arrays and std::array
// Build: g++ -std=c++17 01_arrays.cpp -o arrays && ./arrays

#include <array>
#include <iostream>

int main() {
    // A C-style array: fixed size, inherited from C.
    int dailyRainMm[7] = {0, 12, 5, 0, 30, 8, 2};
    std::cout << "Rain on day 5: " << dailyRainMm[4] << " mm\n";   // index starts at 0

    // std::array: the same fixed size, but it knows its own size.
    std::array<double, 4> quarterlySales = {1.2, 3.4, 2.8, 4.1};   // in lakh rupees
    double yearTotal = 0.0;
    for (double q : quarterlySales) {
        yearTotal += q;
    }
    std::cout << "Quarters: " << quarterlySales.size()
              << ", year total: " << yearTotal << " lakh\n";

    quarterlySales[0] = 1.5;                       // change an element
    std::cout << "Q1 corrected to " << quarterlySales.front()
              << ", last quarter " << quarterlySales.back() << "\n";

    // .at() checks the index and stops the program with an error instead of
    // silently reading the wrong memory. quarterlySales.at(9) would throw.
    std::cout << "Q2 via at(): " << quarterlySales.at(1) << "\n";
    return 0;
}
