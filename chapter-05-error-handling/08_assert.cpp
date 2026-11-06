// C++ in 199 Pages - 5.8 assert and static_assert: checks for programmers
// Build: g++ -std=c++17 08_assert.cpp -o assert && ./assert

#include <cassert>
#include <iostream>
#include <vector>

// static_assert is checked by the compiler. If it fails, nothing builds.
static_assert(sizeof(int) >= 4, "this program needs at least 32-bit int");

constexpr int kMaxPlayers = 4;
static_assert(kMaxPlayers > 1, "a game needs at least two players");

double percentage(int part, int whole) {
    // assert documents a rule that must ALWAYS be true if the code is correct.
    // If it is false, the program stops at once and prints the file and line.
    assert(whole > 0 && "whole must be positive");
    assert(part >= 0 && part <= whole);
    return 100.0 * part / whole;
}

int main() {
    std::cout << "Downloaded: " << percentage(30, 120) << "%\n";

    std::vector<int> scores = {10, 20, 30};
    assert(!scores.empty());
    std::cout << "First score: " << scores.front() << "\n";

    // percentage(5, 0);   // would stop the program: Assertion `whole > 0' failed.
    // Building with -DNDEBUG removes every assert, so never put real work inside one.
    std::cout << "All checks passed.\n";
    return 0;
}
