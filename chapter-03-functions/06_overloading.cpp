// C++ in 199 Pages - 3.6 Function overloading
// Build: g++ -std=c++17 06_overloading.cpp -o overload && ./overload

#include <iostream>
#include <string>

// Same name, different parameter lists. The compiler picks the right one.
double area(double radius) {                       // circle
    return 3.14159 * radius * radius;
}

double area(double width, double height) {         // rectangle
    return width * height;
}

void describe(int value)                { std::cout << "int: " << value << "\n"; }
void describe(double value)             { std::cout << "double: " << value << "\n"; }
void describe(const std::string& value) { std::cout << "text: \"" << value << "\"\n"; }

int main() {
    std::cout << "Circle r=2: " << area(2.0) << "\n";
    std::cout << "Rectangle 3x4: " << area(3.0, 4.0) << "\n";

    describe(42);
    describe(3.5);
    describe(std::string("hello"));
    return 0;
}
