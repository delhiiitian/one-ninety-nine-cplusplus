// C++ in 199 Pages - 4.9 Standard algorithms: sort, find, count and more
// Build: g++ -std=c++17 09_algorithms.cpp -o algorithms && ./algorithms

#include <algorithm>
#include <iostream>
#include <numeric>     // std::accumulate
#include <string>
#include <vector>

struct Player {
    std::string name;
    int score;
};

int main() {
    std::vector<int> marks = {72, 95, 58, 88, 95, 64, 81};

    std::sort(marks.begin(), marks.end());                       // ascending
    std::cout << "Sorted: ";
    for (int m : marks) std::cout << m << " ";
    std::cout << "\n";

    int total = std::accumulate(marks.begin(), marks.end(), 0);
    std::cout << "Total " << total << ", max "
              << *std::max_element(marks.begin(), marks.end()) << "\n";
    std::cout << "How many 95s? " << std::count(marks.begin(), marks.end(), 95) << "\n";

    auto it = std::find(marks.begin(), marks.end(), 88);
    if (it != marks.end()) {
        std::cout << "88 found at sorted position " << (it - marks.begin()) << "\n";
    }

    std::reverse(marks.begin(), marks.end());                    // now descending
    std::cout << "Highest first: " << marks.front() << "\n";

    // Sorting your own structs with a lambda: leaderboard by score, high to low.
    std::vector<Player> board = {{"Ana", 320}, {"Ben", 450}, {"Chi", 280}, {"Dia", 450}};
    std::sort(board.begin(), board.end(), [](const Player& a, const Player& b) {
        if (a.score != b.score) return a.score > b.score;
        return a.name < b.name;                                  // tie-break by name
    });
    for (const Player& p : board) std::cout << p.name << " " << p.score << "\n";

    bool anyBelow300 = std::any_of(board.begin(), board.end(),
                                   [](const Player& p) { return p.score < 300; });
    std::cout << "Anyone below 300? " << (anyBelow300 ? "yes" : "no") << "\n";
    return 0;
}
