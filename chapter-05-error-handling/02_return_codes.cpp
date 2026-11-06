// C++ in 199 Pages - 5.2 Reporting failure with return values
// Build: g++ -std=c++17 02_return_codes.cpp -o retcodes && ./retcodes

#include <iostream>
#include <string>

// Style 1: return a bool for success, put the result in a reference parameter.
bool safeDivide(double a, double b, double& result) {
    if (b == 0.0) {
        return false;
    }
    result = a / b;
    return true;
}

// Style 2: return a status code that says WHAT went wrong.
enum class WithdrawStatus { Ok, InsufficientFunds, InvalidAmount };

WithdrawStatus withdraw(double& balance, double amount) {
    if (amount <= 0) return WithdrawStatus::InvalidAmount;
    if (amount > balance) return WithdrawStatus::InsufficientFunds;
    balance -= amount;
    return WithdrawStatus::Ok;
}

std::string describe(WithdrawStatus s) {
    switch (s) {
        case WithdrawStatus::Ok:                return "OK";
        case WithdrawStatus::InsufficientFunds: return "insufficient funds";
        case WithdrawStatus::InvalidAmount:     return "invalid amount";
    }
    return "unknown";
}

int main() {
    double answer = 0.0;
    if (safeDivide(10, 4, answer)) {
        std::cout << "10 / 4 = " << answer << "\n";
    }
    if (!safeDivide(10, 0, answer)) {
        std::cout << "10 / 0 failed: cannot divide by zero\n";
    }

    double balance = 1000.0;
    for (double amount : {300.0, -5.0, 900.0, 700.0}) {
        WithdrawStatus status = withdraw(balance, amount);
        std::cout << "Withdraw " << amount << ": " << describe(status)
                  << ", balance " << balance << "\n";
    }
    return 0;    // main's own return code: 0 = success to the operating system
}
