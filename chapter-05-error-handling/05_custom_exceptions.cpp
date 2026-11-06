// C++ in 199 Pages - 5.5 Your own exception types
// Build: g++ -std=c++17 05_custom_exceptions.cpp -o custom && ./custom

#include <iostream>
#include <stdexcept>
#include <string>

// Inherit from a standard exception so a catch of std::exception still works.
class OutOfStockError : public std::runtime_error {
public:
    OutOfStockError(const std::string& product, int requested, int available)
        : std::runtime_error("only " + std::to_string(available) + " " + product +
                             " left, " + std::to_string(requested) + " requested"),
          available_(available) {}

    int available() const { return available_; }

private:
    int available_;
};

class PaymentDeclined : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;   // reuse the parent's constructor
};

void placeOrder(int quantity, int stock, double walletBalance, double price) {
    if (quantity > stock) {
        throw OutOfStockError("headphones", quantity, stock);
    }
    if (quantity * price > walletBalance) {
        throw PaymentDeclined("wallet balance too low");
    }
    std::cout << "Order placed for " << quantity << " item(s)\n";
}

int main() {
    int requests[] = {2, 5, 4};
    for (int qty : requests) {
        try {
            placeOrder(qty, 4, 5000.0, 1499.0);
        } catch (const OutOfStockError& e) {
            std::cout << "Out of stock: " << e.what()
                      << ". Offer " << e.available() << " instead?\n";
        } catch (const PaymentDeclined& e) {
            std::cout << "Payment problem: " << e.what() << "\n";
        }
    }
    return 0;
}
