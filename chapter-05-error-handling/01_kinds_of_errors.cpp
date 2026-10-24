// C++ in 199 Pages - 5.1 Three kinds of errors
// Build: g++ -std=c++17 01_kinds_of_errors.cpp -o errors && ./errors

#include <iostream>
#include <vector>

// 1) Compile-time errors: the compiler refuses to build the program.
//    int x = "hello";        // error: cannot convert a string to int
//    std::cout << y;         // error: 'y' was not declared

// 2) Run-time errors: the program builds, but something fails while running.
//    Dividing by zero, reading past the end of a vector, a missing file.

// 3) Logic errors: the program runs "fine" but gives the wrong answer.
double averageBuggy(const std::vector<int>& v) {
    int sum = 0;
    for (int x : v) sum += x;
    return sum / v.size();                 // BUG: integer division
}

double averageFixed(const std::vector<int>& v) {
    if (v.empty()) return 0.0;             // guards a run-time error
    int sum = 0;
    for (int x : v) sum += x;
    return static_cast<double>(sum) / v.size();
}

int main() {
    std::vector<int> ratings = {4, 5, 4, 3};
    std::cout << "Buggy average: " << averageBuggy(ratings) << "\n";   // 4
    std::cout << "Fixed average: " << averageFixed(ratings) << "\n";   // 4
    std::vector<int> moreRatings = {4, 5, 5, 3};
    std::cout << "Buggy average: " << averageBuggy(moreRatings) << "\n";  // 4, wrong
    std::cout << "Fixed average: " << averageFixed(moreRatings) << "\n";  // 4.25
    std::cout << "Empty list:    " << averageFixed({}) << "\n";
    return 0;
}
