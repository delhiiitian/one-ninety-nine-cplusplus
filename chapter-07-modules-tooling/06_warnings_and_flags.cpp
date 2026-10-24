// C++ in 199 Pages - 7.6 Compiler warnings and useful flags
// Build: g++ -std=c++17 -Wall -Wextra -pedantic 06_warnings_and_flags.cpp -o flags && ./flags
//
// Flags worth knowing:
//   -Wall -Wextra -pedantic   turn on the important warnings
//   -Werror                   treat every warning as an error (used in this repo's tests)
//   -O2                       optimise for speed (release builds)
//   -g                        include debug information for gdb
//   -fsanitize=address,undefined   catch memory and undefined-behaviour bugs at run time

#include <iostream>
#include <vector>

int main() {
    std::vector<int> values = {3, 1, 4, 1, 5};

    // WARNING VERSION (do not do this):
    //   for (int i = 0; i < values.size(); ++i)
    //   -> warning: comparison of integer expressions of different signedness
    // FIX: use the same type as size()
    for (std::size_t i = 0; i < values.size(); ++i) {
        std::cout << values[i] << " ";
    }
    std::cout << "\n";

    // WARNING VERSION:   int unused = 42;
    //   -> warning: unused variable 'unused'
    // FIX: delete it, or mark it [[maybe_unused]] if it really must stay.
    [[maybe_unused]] int reservedForLater = 42;

    // WARNING VERSION:   if (int x = 5) ... or  if (total = 0)
    //   -> warning: suggest parentheses around assignment used as truth value
    int total = 0;
    for (int v : values) total += v;
    if (total == 14) {
        std::cout << "Total is 14, built without a single warning.\n";
    }
    return 0;
}
