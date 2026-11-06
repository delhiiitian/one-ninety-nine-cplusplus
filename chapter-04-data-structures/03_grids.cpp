// C++ in 199 Pages - 4.3 Two-dimensional data: a vector of vectors
// Build: g++ -std=c++17 03_grids.cpp -o grids && ./grids

#include <iostream>
#include <vector>

int main() {
    // Tic-tac-toe board: 3 rows, each row is a vector of 3 chars.
    std::vector<std::vector<char>> board(3, std::vector<char>(3, '.'));
    board[0][0] = 'X';
    board[1][1] = 'O';
    board[2][2] = 'X';
    board[0][2] = 'O';

    for (const auto& row : board) {
        for (char cell : row) {
            std::cout << cell << ' ';
        }
        std::cout << "\n";
    }

    // A weekly timetable: hours studied per day (rows) per subject (columns).
    std::vector<std::vector<int>> hours = {
        {2, 1, 0},   // Monday:    Maths, Physics, Chemistry
        {1, 2, 1},   // Tuesday
        {0, 1, 3},   // Wednesday
    };
    std::vector<int> perSubject(3, 0);
    for (std::size_t day = 0; day < hours.size(); ++day) {
        for (std::size_t subject = 0; subject < hours[day].size(); ++subject) {
            perSubject[subject] += hours[day][subject];
        }
    }
    std::cout << "Maths " << perSubject[0] << "h, Physics " << perSubject[1]
              << "h, Chemistry " << perSubject[2] << "h\n";
    return 0;
}
