// C++ in 199 Pages - 1.9 auto and variable scope
// Build: g++ -std=c++17 09_auto_and_scope.cpp -o scope && ./scope

#include <iostream>
#include <string>

int visits = 0;   // global: visible everywhere in this file (use sparingly)

int main() {
    auto count = 3;                 // compiler deduces int
    auto price = 4.5;               // double
    auto name = std::string("Mo");  // std::string

    std::cout << name << " bought " << count << " items at " << price << "\n";

    {   // a new block = a new scope
        int discount = 10;          // only lives inside these braces
        std::cout << "Discount inside block: " << discount << "%\n";
        ++visits;
    }
    // std::cout << discount;       // error: discount is out of scope here

    int count2 = count;             // outer variables are still visible
    {
        int count = 99;             // shadows the outer count (legal but confusing)
        std::cout << "Inner count: " << count << "\n";
    }
    std::cout << "Outer count: " << count2 << ", visits: " << visits << "\n";
    return 0;
}
