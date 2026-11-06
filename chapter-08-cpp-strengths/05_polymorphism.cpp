// C++ in 199 Pages - 8.5 Polymorphism: virtual functions
// Build: g++ -std=c++17 05_polymorphism.cpp -o poly && ./poly

#include <iostream>
#include <memory>
#include <string>
#include <vector>

// An abstract base class: an interface every payment method must follow.
class PaymentMethod {
public:
    virtual ~PaymentMethod() = default;                  // always virtual in a base class
    virtual std::string name() const = 0;                // = 0: "pure", must be overridden
    virtual double fee(double amount) const = 0;
    void pay(double amount) const {                      // shared, non-virtual behaviour
        std::cout << "Paid " << amount << " by " << name()
                  << " (fee " << fee(amount) << ")\n";
    }
};

class Upi : public PaymentMethod {
public:
    std::string name() const override { return "UPI"; }
    double fee(double) const override { return 0.0; }
};

class CreditCard : public PaymentMethod {
public:
    std::string name() const override { return "credit card"; }
    double fee(double amount) const override { return amount * 0.018; }
};

class CashOnDelivery : public PaymentMethod {
public:
    std::string name() const override { return "cash on delivery"; }
    double fee(double) const override { return 40.0; }
};

int main() {
    std::vector<std::unique_ptr<PaymentMethod>> methods;
    methods.push_back(std::make_unique<Upi>());
    methods.push_back(std::make_unique<CreditCard>());
    methods.push_back(std::make_unique<CashOnDelivery>());

    // One loop, three behaviours: each object runs its own version of fee().
    for (const auto& m : methods) {
        m->pay(2000.0);
    }
    return 0;
}
