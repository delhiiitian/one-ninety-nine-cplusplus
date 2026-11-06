// C++ in 199 Pages - 3.8 Lambdas: small functions written in place
// Build: g++ -std=c++17 08_lambdas.cpp -o lambdas && ./lambdas

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main() {
    auto square = [](int x) { return x * x; };
    std::cout << "7 squared: " << square(7) << "\n";

    // Capture: the lambda can use variables from around it.
    double discount = 0.25;
    auto salePrice = [discount](double price) { return price * (1.0 - discount); };
    std::cout << "Sale price of 800: " << salePrice(800.0) << "\n";

    // The most common use: telling an algorithm what to do.
    std::vector<std::string> names = {"Zara", "amit", "Bob", "chen"};
    std::sort(names.begin(), names.end(), [](const std::string& a, const std::string& b) {
        return a.size() < b.size();            // shortest name first
    });
    for (const auto& n : names) std::cout << n << " ";
    std::cout << "\n";

    std::vector<int> ages = {12, 19, 34, 17, 65, 8};
    int adults = static_cast<int>(std::count_if(ages.begin(), ages.end(),
                                                [](int a) { return a >= 18; }));
    std::cout << "Adults: " << adults << "\n";

    // Capture by reference with & to change an outside variable.
    int clicks = 0;
    auto onClick = [&clicks]() { ++clicks; };
    onClick(); onClick(); onClick();
    std::cout << "Button clicked " << clicks << " times\n";
    return 0;
}
