// C++ in 199 Pages - Project 2: Number Guessing Game
// Uses Chapter 2 ideas: if/else, switch, the ternary operator, while,
// do-while, for, break and continue.
//
// Build: make        Run: make run        Test: make test
// Optional: ./guessing_game 42   (a fixed seed gives the same secret numbers
//                                 every time, which is how the test works)

#include <cstdlib>    // std::abs, std::atoi
#include <iostream>
#include <random>     // std::mt19937, a random number engine (Chapter 9)
#include <string>

int main(int argc, char* argv[]) {
    // ---- Section 1: set up the random number engine ------------------------
    std::random_device device;
    unsigned int seed = (argc > 1) ? static_cast<unsigned int>(std::atoi(argv[1]))
                                   : device();
    std::mt19937 rng(seed);

    int gamesPlayed = 0;
    int gamesWon = 0;
    int bestScore = 0;            // fewest guesses in a win, 0 = no wins yet
    char playAgain = 'n';

    std::cout << "=== Guess the Number ===\n";

    // ---- Section 2: the game loop, one round per pass -------------------------
    do {
        std::cout << "\nDifficulty: 1) Easy 1-50  2) Medium 1-100  3) Hard 1-500\n";
        std::cout << "Choose: ";
        int level = 0;
        std::cin >> level;

        int maxNumber = 0;
        int maxAttempts = 0;
        switch (level) {
            case 1:  maxNumber = 50;  maxAttempts = 8;  break;
            case 2:  maxNumber = 100; maxAttempts = 7;  break;
            case 3:  maxNumber = 500; maxAttempts = 9;  break;
            default:
                std::cout << "Unknown level, using Medium.\n";
                maxNumber = 100; maxAttempts = 7;
                break;
        }

        int secret = 1 + static_cast<int>(rng() % static_cast<unsigned int>(maxNumber));
        std::cout << "I picked a number from 1 to " << maxNumber << ". You have "
                  << maxAttempts << " guesses.\n";

        bool won = false;
        int used = 0;

        // ---- Section 3: the guessing loop ---------------------------------------
        for (int attempt = 1; attempt <= maxAttempts; ++attempt) {
            std::cout << "Guess " << attempt << ": ";
            int guess = 0;
            std::cin >> guess;

            if (guess < 1 || guess > maxNumber) {
                std::cout << "  Out of range, this one is free.\n";
                --attempt;                // does not count as a guess
                continue;
            }
            used = attempt;

            if (guess == secret) {
                won = true;
                break;
            }

            int distance = std::abs(guess - secret);
            std::string direction = (guess < secret) ? "higher" : "lower";
            std::string heat = (distance <= 3)  ? "very hot"
                             : (distance <= 10) ? "warm"
                                                : "cold";
            std::cout << "  Go " << direction << " (" << heat << ")\n";
        }

        // ---- Section 4: round result and statistics -----------------------------
        ++gamesPlayed;
        if (won) {
            ++gamesWon;
            std::cout << "Correct! You found " << secret << " in " << used
                      << (used == 1 ? " guess.\n" : " guesses.\n");
            if (bestScore == 0 || used < bestScore) {
                bestScore = used;
                std::cout << "New best score!\n";
            }
        } else {
            std::cout << "Out of guesses. The number was " << secret << ".\n";
        }

        std::cout << "Play again? (y/n): ";
        std::cin >> playAgain;
    } while (playAgain == 'y' || playAgain == 'Y');

    std::cout << "\nGames played: " << gamesPlayed << ", won: " << gamesWon;
    if (bestScore > 0) {
        std::cout << ", best: " << bestScore << " guesses";
    }
    std::cout << "\nThanks for playing!\n";
    return 0;
}
