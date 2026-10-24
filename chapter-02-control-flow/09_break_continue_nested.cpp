// C++ in 199 Pages - 2.9 break, continue and nested loops
// Build: g++ -std=c++17 09_break_continue_nested.cpp -o nested && ./nested

#include <iostream>

int main() {
    // continue: skip one round. Print only odd numbers.
    for (int i = 1; i <= 10; ++i) {
        if (i % 2 == 0) {
            continue;
        }
        std::cout << i << " ";
    }
    std::cout << "\n";

    // break: stop the loop early. Find the first multiple of 7 above 50.
    for (int n = 51; n < 100; ++n) {
        if (n % 7 == 0) {
            std::cout << "First multiple of 7 above 50: " << n << "\n";
            break;
        }
    }

    // Nested loops: a cinema seating chart, rows A-C and seats 1-5.
    for (char row = 'A'; row <= 'C'; ++row) {
        for (int seat = 1; seat <= 5; ++seat) {
            if (row == 'B' && seat == 3) {
                std::cout << "[XX] ";            // a booked seat
                continue;
            }
            std::cout << "[" << row << seat << "] ";
        }
        std::cout << "\n";
    }
    return 0;
}
