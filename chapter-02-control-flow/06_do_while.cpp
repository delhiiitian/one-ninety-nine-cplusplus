// C++ in 199 Pages - 2.6 do-while loops
// Build: g++ -std=c++17 06_do_while.cpp -o dowhile && ./dowhile
// Try:   printf "1234\n0000\n4321\n" | ./dowhile

#include <iostream>
#include <string>

int main() {
    const std::string correctPin = "4321";
    std::string pin;
    int attempts = 0;

    do {                              // the body always runs at least once
        std::cout << "Enter PIN: ";
        std::cin >> pin;
        ++attempts;
        if (pin != correctPin) {
            std::cout << "Wrong PIN.\n";
        }
    } while (pin != correctPin && attempts < 3);

    if (pin == correctPin) {
        std::cout << "Unlocked after " << attempts << " attempt(s).\n";
    } else {
        std::cout << "Card blocked.\n";
    }
    return 0;
}
