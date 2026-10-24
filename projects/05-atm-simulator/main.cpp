// C++ in 199 Pages - Project 5: ATM Simulator
// Uses Chapter 5 ideas: return values, exceptions, a custom exception
// hierarchy, std::optional, input validation, assert and RAII cleanup.
//
// Build: make        Run: make run        Test: make test

#include <cassert>
#include <iostream>
#include <limits>
#include <map>
#include <optional>
#include <stdexcept>
#include <string>
#include <vector>

// ---- Rules of the bank --------------------------------------------------------
constexpr long long kDailyLimit = 20000;   // rupees per card per day
constexpr long long kNoteSize = 100;       // the machine only holds 100-rupee notes
constexpr int kMaxPinAttempts = 3;

// ---- Errors: one family, so callers can catch all of them or just one ----------
class AtmError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};
class InvalidAmount : public AtmError {
public:
    using AtmError::AtmError;
};
class InsufficientFunds : public AtmError {
public:
    using AtmError::AtmError;
};
class DailyLimitExceeded : public AtmError {
public:
    using AtmError::AtmError;
};

// ---- Data -------------------------------------------------------------------------
struct Account {
    std::string holder;
    std::string pin;
    long long balance = 0;          // whole rupees: no floating-point rounding
    long long withdrawnToday = 0;
    bool blocked = false;
    std::vector<std::string> history;
};

using Bank = std::map<std::string, Account>;   // card number -> account

// ---- Input helpers (validation) ---------------------------------------------------
// Returns std::nullopt when input has run out, so callers can stop cleanly.
std::optional<long long> readNumber(const std::string& prompt) {
    while (true) {
        std::cout << prompt;
        long long value = 0;
        if (std::cin >> value) {
            return value;
        }
        if (std::cin.eof()) {
            return std::nullopt;
        }
        std::cout << "\n  Please type digits only.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

std::optional<std::string> readWord(const std::string& prompt) {
    std::cout << prompt;
    std::string word;
    if (std::cin >> word) {
        return word;
    }
    return std::nullopt;
}

// ---- Banking operations: they throw when a rule is broken -------------------------
void checkAmount(long long amount) {
    if (amount <= 0) {
        throw InvalidAmount("amount must be positive");
    }
    if (amount % kNoteSize != 0) {
        throw InvalidAmount("amount must be a multiple of " + std::to_string(kNoteSize));
    }
}

void withdraw(Account& acc, long long amount) {
    checkAmount(amount);
    if (amount > acc.balance) {
        throw InsufficientFunds("balance is only " + std::to_string(acc.balance));
    }
    if (acc.withdrawnToday + amount > kDailyLimit) {
        throw DailyLimitExceeded("you can withdraw " +
                                 std::to_string(kDailyLimit - acc.withdrawnToday) +
                                 " more today");
    }
    acc.balance -= amount;
    acc.withdrawnToday += amount;
    acc.history.push_back("Withdraw  -" + std::to_string(amount));
    assert(acc.balance >= 0);       // must always hold if the checks above are right
}

void deposit(Account& acc, long long amount) {
    checkAmount(amount);
    acc.balance += amount;
    acc.history.push_back("Deposit   +" + std::to_string(amount));
}

void transfer(Bank& bank, Account& from, const std::string& toCard, long long amount) {
    auto it = bank.find(toCard);
    if (it == bank.end()) {
        throw AtmError("no account with card " + toCard);
    }
    if (&it->second == &from) {
        throw AtmError("cannot transfer to the same account");
    }
    checkAmount(amount);
    if (amount > from.balance) {
        throw InsufficientFunds("balance is only " + std::to_string(from.balance));
    }
    from.balance -= amount;
    it->second.balance += amount;
    from.history.push_back("Transfer  -" + std::to_string(amount) + " to " + toCard);
    it->second.history.push_back("Received  +" + std::to_string(amount));
}

// ---- RAII: the card always comes out, however the session ends --------------------
class CardSession {
public:
    explicit CardSession(const std::string& holder) : holder_(holder) {
        std::cout << "\nWelcome, " << holder_ << ".\n";
    }
    ~CardSession() {
        std::cout << "Please take your card. Goodbye, " << holder_ << ".\n";
    }
private:
    std::string holder_;
};

// ---- Login: returns the account, or nothing ---------------------------------------
std::optional<Account*> login(Bank& bank) {
    auto card = readWord("\nInsert card (card number): ");
    if (!card) return std::nullopt;

    auto it = bank.find(*card);
    if (it == bank.end()) {
        std::cout << "Card not recognised.\n";
        return std::nullopt;
    }
    Account& acc = it->second;
    if (acc.blocked) {
        std::cout << "This card is blocked. Please contact your branch.\n";
        return std::nullopt;
    }
    for (int attempt = 1; attempt <= kMaxPinAttempts; ++attempt) {
        auto pin = readWord("PIN: ");
        if (!pin) return std::nullopt;
        if (*pin == acc.pin) {
            return &acc;
        }
        std::cout << "Wrong PIN (" << kMaxPinAttempts - attempt << " tries left).\n";
    }
    acc.blocked = true;
    std::cout << "Too many wrong PINs. Card blocked.\n";
    return std::nullopt;
}

// ---- One customer's session ---------------------------------------------------------
void runSession(Bank& bank, Account& acc) {
    CardSession session(acc.holder);
    while (true) {
        auto choice = readNumber(
            "\n1) Balance 2) Withdraw 3) Deposit 4) Transfer 5) Mini statement 6) Exit\nChoose: ");
        if (!choice || *choice == 6) {
            return;                                  // ~CardSession runs here
        }
        try {
            switch (*choice) {
                case 1:
                    std::cout << "\nBalance: " << acc.balance << "\n";
                    break;
                case 2: {
                    auto amount = readNumber("Amount: ");
                    if (!amount) return;
                    withdraw(acc, *amount);
                    std::cout << "\nPlease collect " << *amount / kNoteSize << " notes of "
                              << kNoteSize << ". Balance: " << acc.balance << "\n";
                    break;
                }
                case 3: {
                    auto amount = readNumber("Amount: ");
                    if (!amount) return;
                    deposit(acc, *amount);
                    std::cout << "\nDeposited. Balance: " << acc.balance << "\n";
                    break;
                }
                case 4: {
                    auto to = readWord("To card: ");
                    auto amount = readNumber("Amount: ");
                    if (!to || !amount) return;
                    transfer(bank, acc, *to, *amount);
                    std::cout << "\nTransferred. Balance: " << acc.balance << "\n";
                    break;
                }
                case 5:
                    std::cout << "\nLast transactions:\n";
                    for (const std::string& line : acc.history) {
                        std::cout << "  " << line << "\n";
                    }
                    if (acc.history.empty()) std::cout << "  (none)\n";
                    break;
                default:
                    std::cout << "\nUnknown option.\n";
            }
        } catch (const InsufficientFunds& e) {
            std::cout << "\nDeclined: insufficient funds, " << e.what() << ".\n";
        } catch (const DailyLimitExceeded& e) {
            std::cout << "\nDeclined: daily limit reached, " << e.what() << ".\n";
        } catch (const AtmError& e) {                // InvalidAmount and the rest
            std::cout << "\nError: " << e.what() << ".\n";
        }
    }
}

int main() {
    Bank bank = {
        {"4001", {"Anil Kumar", "1234", 25000, 0, false, {}}},
        {"4002", {"Fatima Sheikh", "8080", 3200, 0, false, {}}},
    };
    std::cout << "=== 199 Bank ATM ===\n";

    // Serve customers until the input runs out.
    while (std::cin) {
        std::optional<Account*> acc = login(bank);
        if (acc) {
            runSession(bank, **acc);
        }
    }
    std::cout << "\nATM shutting down.\n";
    return 0;
}
