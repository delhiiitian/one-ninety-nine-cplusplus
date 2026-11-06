// C++ in 199 Pages - Project 7: a tiny test framework (see lesson 7.8).
#pragma once

#include <cmath>
#include <iostream>

namespace testing {
inline int run = 0;
inline int failed = 0;

inline int summary() {
    std::cout << run - failed << "/" << run << " checks passed\n";
    return failed == 0 ? 0 : 1;
}
}  // namespace testing

#define CHECK(condition)                                                          \
    do {                                                                          \
        ++testing::run;                                                           \
        if (!(condition)) {                                                       \
            ++testing::failed;                                                    \
            std::cout << "FAIL " << __FILE__ << ":" << __LINE__ << "  " #condition "\n"; \
        }                                                                         \
    } while (false)

#define CHECK_NEAR(actual, expected) CHECK(std::abs((actual) - (expected)) < 1e-6)

#define CHECK_THROWS(statement)                                                   \
    do {                                                                          \
        bool threw = false;                                                       \
        try { statement; } catch (...) { threw = true; }                          \
        CHECK(threw && "expected an exception: " #statement);                     \
    } while (false)
