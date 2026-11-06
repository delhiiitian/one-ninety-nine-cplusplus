// C++ in 199 Pages - 3.9 Declarations (prototypes) and definitions
// Build: g++ -std=c++17 09_declarations.cpp -o declare && ./declare

#include <iostream>

// Declarations: promise the compiler these functions exist.
// Now main() can call them even though their bodies come later.
bool isEven(int n);
bool isOdd(int n);
int collatzSteps(int n);

int main() {
    std::cout << "7 is " << (isOdd(7) ? "odd" : "even") << "\n";
    std::cout << "10 is " << (isEven(10) ? "even" : "odd") << "\n";
    std::cout << "Collatz steps for 27: " << collatzSteps(27) << "\n";
    return 0;
}

// Definitions: the actual bodies.
// isEven and isOdd call each other, which only works with declarations.
bool isEven(int n) {
    return n == 0 ? true : isOdd(n - 1);
}

bool isOdd(int n) {
    return n == 0 ? false : isEven(n - 1);
}

int collatzSteps(int n) {
    int steps = 0;
    while (n != 1) {
        n = (n % 2 == 0) ? n / 2 : 3 * n + 1;
        ++steps;
    }
    return steps;
}
