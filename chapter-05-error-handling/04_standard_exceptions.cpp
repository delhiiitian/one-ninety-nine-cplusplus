// C++ in 199 Pages - 5.4 Standard exception types
// Build: g++ -std=c++17 04_standard_exceptions.cpp -o stdexcept && ./stdexcept

#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

void tryIt(const std::string& label, void (*action)()) {
    try {
        action();
        std::cout << label << ": ok\n";
    } catch (const std::out_of_range& e) {           // most specific first
        std::cout << label << ": out_of_range -> " << e.what() << "\n";
    } catch (const std::invalid_argument& e) {
        std::cout << label << ": invalid_argument -> " << e.what() << "\n";
    } catch (const std::exception& e) {              // any standard exception
        std::cout << label << ": exception -> " << e.what() << "\n";
    }
}

int main() {
    tryIt("vector.at(10)", [] {
        std::vector<int> v = {1, 2, 3};
        std::cout << v.at(10);
    });
    tryIt("stoi(\"abc\")", [] {
        std::cout << std::stoi("abc");
    });
    tryIt("stoi(\"99999999999\")", [] {
        std::cout << std::stoi("99999999999");      // too big: out_of_range
    });
    tryIt("map.at(\"Mars\")", [] {
        std::map<std::string, int> moons = {{"Earth", 1}};
        std::cout << moons.at("Mars");
    });
    tryIt("runtime_error", [] {
        throw std::runtime_error("payment gateway timed out");
    });
    tryIt("stoi(\"42\")", [] {
        std::cout << std::stoi("42") << " ";
    });
    return 0;
}
