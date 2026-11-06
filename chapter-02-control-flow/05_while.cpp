// C++ in 199 Pages - 2.5 while loops
// Build: g++ -std=c++17 05_while.cpp -o while && ./while

#include <iostream>

int main() {
    // Savings: how many months until we reach the goal?
    double balance = 0.0;
    double monthlyDeposit = 2500.0;
    double goal = 12000.0;
    int months = 0;

    while (balance < goal) {          // check first, then run the body
        balance += monthlyDeposit;
        ++months;
        std::cout << "Month " << months << ": " << balance << "\n";
    }
    std::cout << "Goal reached in " << months << " months.\n";

    // Count down
    int seconds = 3;
    while (seconds > 0) {
        std::cout << seconds << "... ";
        --seconds;
    }
    std::cout << "Lift off!\n";
    return 0;
}
