// C++ in 199 Pages - 5.7 Validating user input
// Build: g++ -std=c++17 07_input_validation.cpp -o validate && ./validate
// Try:   printf "abc\n-3\n200\n42\n" | ./validate

#include <iostream>
#include <limits>

// Keep asking until the user types a whole number between low and high.
int readIntInRange(const char* prompt, int low, int high) {
    while (true) {
        std::cout << prompt;
        int value = 0;
        if (std::cin >> value) {
            if (value >= low && value <= high) {
                return value;
            }
            std::cout << "  Please enter a number from " << low << " to " << high << ".\n";
        } else {
            if (std::cin.eof()) {                // no more input at all
                std::cout << "\n  No input, using " << low << ".\n";
                return low;
            }
            std::cout << "  That is not a number.\n";
            std::cin.clear();                    // 1) clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // 2) discard the bad line
        }
    }
}

int main() {
    int age = readIntInRange("Enter your age (1-120): ", 1, 120);
    std::cout << "Thanks, age " << age << " recorded.\n";
    return 0;
}
