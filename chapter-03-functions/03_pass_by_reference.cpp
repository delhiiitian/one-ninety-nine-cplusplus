// C++ in 199 Pages - 3.3 Pass by value vs pass by reference
// Build: g++ -std=c++17 03_pass_by_reference.cpp -o byref && ./byref

#include <iostream>

void addBonusByValue(int points) {        // gets a COPY
    points += 50;
    std::cout << "  inside (copy): " << points << "\n";
}

void addBonusByReference(int& points) {   // gets the ORIGINAL
    points += 50;
    std::cout << "  inside (original): " << points << "\n";
}

void swapValues(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

int main() {
    int score = 100;
    addBonusByValue(score);
    std::cout << "After by-value call: " << score << "\n";      // still 100

    addBonusByReference(score);
    std::cout << "After by-reference call: " << score << "\n";  // now 150

    int left = 1, right = 2;
    swapValues(left, right);
    std::cout << "Swapped: left=" << left << " right=" << right << "\n";
    return 0;
}
