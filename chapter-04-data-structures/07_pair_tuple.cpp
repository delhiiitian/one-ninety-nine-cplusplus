// C++ in 199 Pages - 4.7 std::pair and std::tuple
// Build: g++ -std=c++17 07_pair_tuple.cpp -o pairs && ./pairs

#include <iostream>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

// Return two values at once with a pair.
std::pair<int, int> minAndMax(const std::vector<int>& values) {
    int lo = values[0], hi = values[0];
    for (int v : values) {
        if (v < lo) lo = v;
        if (v > hi) hi = v;
    }
    return {lo, hi};
}

// Return three values with a tuple.
std::tuple<std::string, int, double> topSeller() {
    return {"Masala Dosa", 182, 90.0};
}

int main() {
    std::pair<std::string, int> city("Pune", 411001);
    std::cout << city.first << " PIN " << city.second << "\n";

    auto [lowest, highest] = minAndMax({31, 27, 35, 29, 38, 33});
    std::cout << "Temperatures this week: " << lowest << " to " << highest << " C\n";

    auto [dish, sold, price] = topSeller();
    std::cout << "Top seller: " << dish << ", " << sold << " plates, revenue "
              << sold * price << "\n";

    std::tuple<int, int, int> date{2026, 10, 24};
    std::cout << "Year from tuple: " << std::get<0>(date) << "\n";
    return 0;
}
