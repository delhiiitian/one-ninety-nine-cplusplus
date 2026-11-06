// C++ in 199 Pages - 7.5 Build tools: Make and CMake
// Build with Make:   make && ./greeter
// Build with CMake:  cmake -S . -B build && cmake --build build && ./build/greeter

#include <iostream>
#include "greeting.h"

int main() {
    std::cout << greet("Priya", 9) << "\n";
    std::cout << greet("Priya", 14) << "\n";
    std::cout << greet("Priya", 20) << "\n";
    return 0;
}
