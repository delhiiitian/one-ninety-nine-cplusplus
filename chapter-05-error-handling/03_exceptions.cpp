// C++ in 199 Pages - 5.3 Exceptions: throw, try and catch
// Build: g++ -std=c++17 03_exceptions.cpp -o exceptions && ./exceptions

#include <iostream>
#include <stdexcept>
#include <string>

double ticketPrice(int age) {
    if (age < 0 || age > 130) {
        throw std::invalid_argument("age must be between 0 and 130, got " +
                                    std::to_string(age));
    }
    if (age < 5) return 0.0;
    if (age < 12) return 150.0;
    return 250.0;
}

double groupTotal(int a, int b, int c) {
    // No try here: if ticketPrice throws, the exception flies straight
    // past this function to whoever is ready to catch it.
    return ticketPrice(a) + ticketPrice(b) + ticketPrice(c);
}

int main() {
    try {
        std::cout << "Family of 3: " << groupTotal(38, 9, 3) << "\n";
        std::cout << "Typo group: " << groupTotal(40, -2, 7) << "\n";   // throws
        std::cout << "This line never runs\n";
    } catch (const std::invalid_argument& e) {
        std::cout << "Could not price tickets: " << e.what() << "\n";
    }
    std::cout << "The program carries on after the catch.\n";
    return 0;
}
