// C++ in 199 Pages - 4.2 std::vector: a list that grows
// Build: g++ -std=c++17 02_vector.cpp -o vector && ./vector

#include <iostream>
#include <string>
#include <vector>

void printCart(const std::vector<std::string>& cart) {
    std::cout << "Cart (" << cart.size() << "): ";
    for (const auto& item : cart) {
        std::cout << item << ", ";
    }
    std::cout << "\n";
}

int main() {
    std::vector<std::string> cart;          // starts empty
    cart.push_back("Milk");                 // add to the end
    cart.push_back("Bread");
    cart.push_back("Eggs");
    cart.push_back("Tea");
    printCart(cart);

    cart[1] = "Brown bread";                // change by index
    cart.pop_back();                        // remove the last item
    cart.erase(cart.begin());               // remove the first item
    cart.insert(cart.begin(), "Butter");    // insert at the front
    printCart(cart);

    std::vector<int> scores(5, 0);          // five zeros
    for (std::size_t i = 0; i < scores.size(); ++i) {
        scores[i] = static_cast<int>(i) * 10;
    }
    std::cout << "Last score: " << scores.back() << ", empty? "
              << std::boolalpha << scores.empty() << "\n";

    cart.clear();
    std::cout << "After clear, empty? " << cart.empty() << "\n";
    return 0;
}
