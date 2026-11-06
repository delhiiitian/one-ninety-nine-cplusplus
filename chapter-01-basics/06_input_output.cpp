// C++ in 199 Pages - 1.6 Input and output with cin and cout
// Build: g++ -std=c++17 06_input_output.cpp -o io && ./io
// Try:   echo "Asha 3" | ./io

#include <iostream>
#include <string>

int main() {
    std::string name;
    int cups = 0;

    std::cout << "What is your name? ";
    std::cin >> name;                       // reads one word
    std::cout << "How many cups of tea today? ";
    std::cin >> cups;                       // reads a number

    std::cout << "\nHi " << name << "! " << cups << " cups is "
              << cups * 40 << " mg of caffeine.\n";
    return 0;
}
