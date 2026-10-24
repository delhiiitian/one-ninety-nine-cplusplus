// C++ in 199 Pages - 3.5 Default arguments
// Build: g++ -std=c++17 05_default_arguments.cpp -o defaults && ./defaults

#include <iostream>
#include <string>

// Parameters with defaults must come last.
void orderPizza(const std::string& size, const std::string& crust = "regular",
                int extraCheese = 0) {
    std::cout << size << " pizza, " << crust << " crust";
    if (extraCheese > 0) {
        std::cout << ", " << extraCheese << "x extra cheese";
    }
    std::cout << "\n";
}

double priceWithTax(double price, double taxRate = 0.18) {
    return price * (1.0 + taxRate);
}

int main() {
    orderPizza("Medium");                    // uses both defaults
    orderPizza("Large", "thin");             // uses one default
    orderPizza("Small", "cheese-burst", 2);  // no defaults used

    std::cout << "With standard tax: " << priceWithTax(100.0) << "\n";
    std::cout << "With 5% tax: " << priceWithTax(100.0, 0.05) << "\n";
    return 0;
}
