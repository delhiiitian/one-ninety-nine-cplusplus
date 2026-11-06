// C++ in 199 Pages - 7.8 Unit testing: code that checks your code
// Build: g++ -std=c++17 08_unit_testing.cpp -o tests && ./tests
//
// Real projects use a framework such as GoogleTest or Catch2. This file builds
// a tiny one so you can see that a test is just code that compares results.

#include <cmath>
#include <iostream>
#include <string>

int testsRun = 0;
int testsFailed = 0;

#define CHECK(condition)                                                        \
    do {                                                                        \
        ++testsRun;                                                             \
        if (!(condition)) {                                                     \
            ++testsFailed;                                                      \
            std::cout << "  FAIL line " << __LINE__ << ": " #condition "\n";   \
        }                                                                       \
    } while (false)

// ---- Code under test ----
bool isPalindrome(const std::string& s) {
    for (std::size_t i = 0, j = s.size(); i < j; ++i) {
        --j;
        if (s[i] != s[j]) return false;
    }
    return true;
}

double emi(double principal, double annualRatePercent, int months) {
    if (annualRatePercent == 0.0) return principal / months;
    double r = annualRatePercent / 12.0 / 100.0;
    double factor = std::pow(1 + r, months);
    return principal * r * factor / (factor - 1);
}

// ---- Tests ----
void testPalindrome() {
    CHECK(isPalindrome("level"));
    CHECK(isPalindrome("abba"));
    CHECK(isPalindrome(""));             // edge case: empty string
    CHECK(isPalindrome("a"));            // edge case: one character
    CHECK(!isPalindrome("hello"));
}

void testEmi() {
    CHECK(std::abs(emi(120000, 0, 12) - 10000) < 0.01);       // no interest
    CHECK(std::abs(emi(100000, 12, 12) - 8884.88) < 0.01);    // known bank figure
    CHECK(emi(500000, 9, 60) > 500000.0 / 60);                // interest makes it bigger
}

int main() {
    std::cout << "Running tests...\n";
    testPalindrome();
    testEmi();
    std::cout << testsRun - testsFailed << "/" << testsRun << " checks passed\n";
    return testsFailed == 0 ? 0 : 1;      // non-zero tells build tools a test failed
}
