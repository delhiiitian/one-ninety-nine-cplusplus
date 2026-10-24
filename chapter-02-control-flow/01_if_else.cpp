// C++ in 199 Pages - 2.1 if and else
// Build: g++ -std=c++17 01_if_else.cpp -o ifelse && ./ifelse
// Try:   echo 17 | ./ifelse

#include <iostream>

int main() {
    int age = 0;
    std::cout << "Enter your age: ";
    std::cin >> age;

    if (age >= 18) {
        std::cout << "\nYou can apply for a driving licence.\n";
    } else {
        std::cout << "\nYou can apply in " << 18 - age << " year(s).\n";
    }

    // Comparison operators: == != < > <= >=
    bool isTeen = (age >= 13 && age <= 19);
    if (isTeen) {
        std::cout << "You are a teenager.\n";
    }
    return 0;
}
