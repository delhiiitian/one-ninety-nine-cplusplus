// C++ in 199 Pages - 2.4 The ternary operator ? :
// Build: g++ -std=c++17 04_ternary.cpp -o ternary && ./ternary

#include <iostream>
#include <string>

int main() {
    int itemsInCart = 1;
    std::string word = (itemsInCart == 1) ? "item" : "items";
    std::cout << "You have " << itemsInCart << " " << word << " in your cart.\n";

    double orderTotal = 420.0;
    double delivery = (orderTotal >= 500.0) ? 0.0 : 40.0;
    std::cout << "Delivery charge: " << delivery << "\n";

    int a = 7, b = 12;
    int larger = (a > b) ? a : b;
    std::cout << "Larger of " << a << " and " << b << " is " << larger << "\n";
    return 0;
}
