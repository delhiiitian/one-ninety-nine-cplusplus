// C++ in 199 Pages - 1.5 Arithmetic and assignment operators
// Build: g++ -std=c++17 05_operators.cpp -o operators && ./operators

#include <iostream>

int main() {
    int cookies = 17;
    int kids = 5;

    std::cout << "Each kid gets: " << cookies / kids << "\n";   // 3 (integer division)
    std::cout << "Left over: "     << cookies % kids << "\n";   // 2 (remainder)
    std::cout << "Half the cookies: " << cookies / 2.0 << "\n";        // 8.5 (a double joins in)

    int score = 10;
    score += 5;    // score = score + 5  -> 15
    score *= 2;    // score = score * 2  -> 30
    score -= 4;    // -> 26
    ++score;       // -> 27
    std::cout << "Score: " << score << "\n";

    // Precedence: * and / happen before + and -
    int a = 2 + 3 * 4;      // 14
    int b = (2 + 3) * 4;    // 20
    std::cout << "2 + 3 * 4 = " << a << ", (2 + 3) * 4 = " << b << "\n";
    return 0;
}
