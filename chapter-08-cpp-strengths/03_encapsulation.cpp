// C++ in 199 Pages - 8.3 Encapsulation: private data, public rules
// Build: g++ -std=c++17 03_encapsulation.cpp -o encap && ./encap

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

class BankAccount {
public:
    explicit BankAccount(const std::string& owner) : owner_(owner) {}

    void deposit(long long amount) {
        if (amount <= 0) throw std::invalid_argument("deposit must be positive");
        balance_ += amount;
        log_.push_back("+" + std::to_string(amount));
    }

    bool withdraw(long long amount) {
        if (amount <= 0 || amount > balance_) return false;   // the rule is enforced HERE
        balance_ -= amount;
        log_.push_back("-" + std::to_string(amount));
        return true;
    }

    // Getters give read-only access. There is deliberately no setBalance().
    long long balance() const { return balance_; }
    const std::string& owner() const { return owner_; }
    std::size_t transactionCount() const { return log_.size(); }

private:
    std::string owner_;
    long long balance_ = 0;            // nobody outside can write account.balance_ = 1000000
    std::vector<std::string> log_;
};

int main() {
    BankAccount acc("Farhan");
    acc.deposit(5000);
    std::cout << "Withdraw 2000: " << (acc.withdraw(2000) ? "ok" : "refused") << "\n";
    std::cout << "Withdraw 9000: " << (acc.withdraw(9000) ? "ok" : "refused") << "\n";
    // acc.balance_ = 1000000;   // error: 'balance_' is private
    std::cout << acc.owner() << " has " << acc.balance() << " after "
              << acc.transactionCount() << " transactions\n";
    return 0;
}
