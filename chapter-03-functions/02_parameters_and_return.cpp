// C++ in 199 Pages - 3.2 Parameters and return values
// Build: g++ -std=c++17 02_parameters_and_return.cpp -o params && ./params

#include <iostream>
#include <string>

// Takes two inputs (parameters) and gives back one output (return value).
double rectangleArea(double width, double height) {
    return width * height;
}

double celsiusToFahrenheit(double celsius) {
    return celsius * 9.0 / 5.0 + 32.0;
}

bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

std::string initials(const std::string& first, const std::string& last) {
    return std::string(1, first[0]) + "." + last[0] + ".";
}

int main() {
    double room = rectangleArea(4.0, 3.5);
    std::cout << "Room area: " << room << " square metres\n";
    std::cout << "37 C = " << celsiusToFahrenheit(37.0) << " F\n";

    for (int year : {1900, 2000, 2024, 2025}) {
        std::cout << year << (isLeapYear(year) ? " is" : " is not") << " a leap year\n";
    }
    std::cout << "Initials: " << initials("Grace", "Hopper") << "\n";
    return 0;
}
