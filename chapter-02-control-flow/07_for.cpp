// C++ in 199 Pages - 2.7 for loops
// Build: g++ -std=c++17 07_for.cpp -o for && ./for

#include <iostream>

int main() {
    // Times table for 7
    for (int i = 1; i <= 10; ++i) {
        std::cout << "7 x " << i << " = " << 7 * i << "\n";
    }

    // Counting in steps: every 15 minutes in an hour
    for (int minute = 0; minute < 60; minute += 15) {
        std::cout << "10:" << (minute < 10 ? "0" : "") << minute << " ";
    }
    std::cout << "\n";

    // Adding up: total of 1 to 100
    int sum = 0;
    for (int n = 1; n <= 100; ++n) {
        sum += n;
    }
    std::cout << "1 + 2 + ... + 100 = " << sum << "\n";
    return 0;
}
