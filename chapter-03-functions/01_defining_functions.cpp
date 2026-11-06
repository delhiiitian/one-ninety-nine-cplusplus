// C++ in 199 Pages - 3.1 Defining and calling functions
// Build: g++ -std=c++17 01_defining_functions.cpp -o functions && ./functions

#include <iostream>

// A function is a named, reusable block of code.
void printDivider() {
    std::cout << "------------------------------\n";
}

void greetCustomer() {
    std::cout << "Welcome to Corner Bakery!\n";
    std::cout << "Fresh bread every morning at 7.\n";
}

int main() {
    printDivider();          // call it: the code inside runs now
    greetCustomer();
    printDivider();
    greetCustomer();         // reuse without copying the lines
    printDivider();
    return 0;
}
