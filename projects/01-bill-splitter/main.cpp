// C++ in 199 Pages - Project 1: Restaurant Bill Splitter
// Uses only Chapter 1 ideas: variables, constants, arithmetic, strings,
// type conversion, and console input/output.
//
// Build: make        Run: make run        Test: make test

#include <iomanip>    // std::fixed, std::setprecision for money formatting
#include <iostream>
#include <string>

// ---- Section 1: fixed rules of the restaurant ------------------------------
constexpr double kServiceTaxRate = 0.05;   // 5% tax on the food bill
constexpr int kReceiptWidth = 32;          // characters per receipt line

int main() {
    // ---- Section 2: collect the inputs -------------------------------------
    std::string restaurant;
    double foodBill = 0.0;
    int tipPercent = 0;
    int people = 1;

    std::cout << "Restaurant name: ";
    std::getline(std::cin, restaurant);     // the whole line, spaces included
    std::cout << "Food bill amount: ";
    std::cin >> foodBill;
    std::cout << "Tip percent (e.g. 10): ";
    std::cin >> tipPercent;
    std::cout << "Number of people: ";
    std::cin >> people;

    // ---- Section 3: the calculation ----------------------------------------
    double tax   = foodBill * kServiceTaxRate;
    double tip   = foodBill * (static_cast<double>(tipPercent) / 100.0);
    double total = foodBill + tax + tip;
    double share = total / people;

    // Round each share UP to the next whole unit so the table never comes up short.
    int roundedShare = static_cast<int>(share);
    if (share > roundedShare) {               // tiny preview of Chapter 2
        roundedShare = roundedShare + 1;
    }
    double collected = static_cast<double>(roundedShare) * people;
    double extraForTip = collected - total;

    // ---- Section 4: print the receipt --------------------------------------
    std::string line(kReceiptWidth, '=');     // a string of 32 '=' characters
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "\n" << line << "\n";
    std::cout << "  " << restaurant << "\n";
    std::cout << line << "\n";
    std::cout << "Food bill      : " << std::setw(10) << foodBill << "\n";
    std::cout << "Service tax 5% : " << std::setw(10) << tax << "\n";
    std::cout << "Tip " << std::setw(3) << tipPercent << "%       : "
              << std::setw(10) << tip << "\n";
    std::cout << std::string(kReceiptWidth, '-') << "\n";
    std::cout << "Total          : " << std::setw(10) << total << "\n";
    std::cout << "People         : " << std::setw(10) << people << "\n";
    std::cout << "Exact share    : " << std::setw(10) << share << "\n";
    std::cout << "Pay (rounded)  : " << std::setw(10) << roundedShare << "\n";
    std::cout << "Extra tip left : " << std::setw(10) << extraForTip << "\n";
    std::cout << line << "\n";
    return 0;
}
