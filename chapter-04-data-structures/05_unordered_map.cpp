// C++ in 199 Pages - 4.5 std::unordered_map: the fastest lookups
// Build: g++ -std=c++17 05_unordered_map.cpp -o umap && ./umap

#include <iostream>
#include <string>
#include <unordered_map>

int main() {
    // Product code -> price. Order does not matter, speed does.
    std::unordered_map<std::string, double> prices = {
        {"SKU-1001", 49.0},
        {"SKU-2002", 120.0},
        {"SKU-3003", 15.5},
    };
    prices["SKU-4004"] = 300.0;

    std::string scanned[] = {"SKU-2002", "SKU-3003", "SKU-9999", "SKU-3003"};
    double bill = 0.0;
    for (const std::string& code : scanned) {
        auto it = prices.find(code);
        if (it != prices.end()) {
            std::cout << code << " : " << it->second << "\n";
            bill += it->second;
        } else {
            std::cout << code << " : unknown product\n";
        }
    }
    std::cout << "Bill: " << bill << "\n";
    std::cout << "Products in catalogue: " << prices.size() << "\n";

    // contains() would need C++20, so we use count() here.
    std::cout << "Has SKU-1001? " << (prices.count("SKU-1001") ? "yes" : "no") << "\n";
    return 0;
}
