// C++ in 199 Pages - 1.2 Comments and code style
// Build: g++ -std=c++17 02_comments_and_style.cpp -o comments && ./comments

#include <iostream>

/*
 * A block comment can span many lines.
 * Use it for a short explanation at the top of a file or function.
 */

// Good names explain themselves, so you need fewer comments.
int main() {
    int minutesPerHour = 60;           // camelCase name: says what it holds
    int hoursWorked = 8;

    // Explain WHY, not WHAT. The code already says what.
    // We pay by the minute because the client asked for it.
    int billableMinutes = hoursWorked * minutesPerHour;

    std::cout << "Billable minutes today: " << billableMinutes << "\n";

    // int unused = 42;   <- commented-out code is ignored by the compiler
    return 0;
}
