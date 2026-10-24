// C++ in 199 Pages - 2.8 Range-based for loops
// Build: g++ -std=c++17 08_range_for.cpp -o rangefor && ./rangefor

#include <iostream>
#include <string>
#include <vector>

int main() {
    std::vector<std::string> playlist = {"Intro", "Sunrise", "Rain", "Outro"};

    int track = 1;
    for (const std::string& song : playlist) {   // "for each song in playlist"
        std::cout << track << ". " << song << "\n";
        ++track;
    }

    std::vector<double> prices = {120.0, 80.5, 45.0};
    for (double& p : prices) {                   // & lets us change each item
        p = p * 0.9;                             // 10% off everything
    }
    for (double p : prices) {
        std::cout << p << " ";
    }
    std::cout << "\n";

    std::string word = "loop";
    for (char c : word) {                        // strings work too
        std::cout << c << "-";
    }
    std::cout << "\n";
    return 0;
}
