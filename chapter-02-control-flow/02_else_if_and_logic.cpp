// C++ in 199 Pages - 2.2 else if chains and logical operators
// Build: g++ -std=c++17 02_else_if_and_logic.cpp -o elseif && ./elseif

#include <iostream>

int main() {
    int temperatures[] = {-3, 12, 24, 38};   // a small list to test every branch

    for (int t : temperatures) {             // loops come later in this chapter
        std::cout << t << " C: ";
        if (t < 0) {
            std::cout << "Freezing. Wear a heavy coat.\n";
        } else if (t < 15) {
            std::cout << "Cold. Take a jacket.\n";
        } else if (t < 30) {
            std::cout << "Pleasant. T-shirt weather.\n";
        } else {
            std::cout << "Hot. Drink water.\n";
        }
    }

    // && (and), || (or), ! (not)
    bool hasTicket = true;
    bool hasId = false;
    bool isVip = true;
    if ((hasTicket && hasId) || isVip) {
        std::cout << "Entry allowed.\n";
    }
    if (!hasId) {
        std::cout << "Reminder: bring ID next time.\n";
    }
    return 0;
}
