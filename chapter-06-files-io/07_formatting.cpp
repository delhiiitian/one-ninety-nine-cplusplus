// C++ in 199 Pages - 6.7 Formatting output with <iomanip>
// Build: g++ -std=c++17 07_formatting.cpp -o format && ./format

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

struct Row {
    std::string city;
    double tempC;
    int humidity;
};

int main() {
    std::vector<Row> weather = {{"Delhi", 31.456, 40}, {"Mumbai", 29.9, 78},
                                {"Bengaluru", 24.25, 61}, {"Leh", 8.0, 22}};

    std::cout << std::left << std::setw(12) << "City"
              << std::right << std::setw(8) << "Temp C"
              << std::setw(10) << "Humidity" << "\n";
    std::cout << std::setfill('-') << std::setw(30) << "" << std::setfill(' ') << "\n";

    std::cout << std::fixed << std::setprecision(1);
    for (const Row& r : weather) {
        std::cout << std::left << std::setw(12) << r.city
                  << std::right << std::setw(8) << r.tempC
                  << std::setw(9) << r.humidity << "%\n";
    }

    // Zero-padded numbers, like invoice IDs and times
    std::cout << "Invoice INV-" << std::setw(6) << std::setfill('0') << 42 << "\n";
    std::cout << std::setfill(' ');
    std::cout << "Time " << std::setw(2) << std::setfill('0') << 9 << ":"
              << std::setw(2) << 5 << std::setfill(' ') << "\n";

    std::cout << std::setprecision(3) << "Pi to 3 places: " << 3.14159265 << "\n";
    std::cout << std::hex << "255 in hex: " << 255 << std::dec << "\n";
    return 0;
}
