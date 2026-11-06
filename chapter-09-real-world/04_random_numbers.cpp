// C++ in 199 Pages - 9.4 Random numbers with <random>
// Build: g++ -std=c++17 04_random_numbers.cpp -o dice && ./dice

#include <algorithm>
#include <iostream>
#include <map>
#include <random>
#include <string>
#include <vector>

int main() {
    // An engine makes raw random bits; a distribution shapes them.
    std::mt19937 rng(2024);   // fixed seed: the same "random" sequence every run

    std::uniform_int_distribution<int> die(1, 6);
    std::cout << "Five dice rolls:";
    for (int i = 0; i < 5; ++i) std::cout << " " << die(rng);
    std::cout << "\n";

    // Roll 6000 times and count: each face should appear about 1000 times.
    std::map<int, int> counts;
    for (int i = 0; i < 6000; ++i) ++counts[die(rng)];
    bool fair = std::all_of(counts.begin(), counts.end(),
                            [](const auto& entry) { return entry.second > 900 && entry.second < 1100; });
    std::cout << "6000 rolls look fair: " << (fair ? "yes" : "no") << "\n";

    // A real number between 0 and 1, for example a discount chance.
    std::uniform_real_distribution<double> chance(0.0, 1.0);
    int winners = 0;
    for (int i = 0; i < 1000; ++i) if (chance(rng) < 0.1) ++winners;
    std::cout << "About 10% won a coupon: " << (winners > 70 && winners < 130 ? "yes" : "no") << "\n";

    // Shuffle a playlist.
    std::vector<std::string> songs{"Intro", "Monsoon", "Chai", "Highway", "Finale"};
    std::mt19937 playlistRng(7);                       // its own seeded engine
    std::shuffle(songs.begin(), songs.end(), playlistRng);
    std::cout << "Shuffled playlist:";
    for (const std::string& song : songs) std::cout << " " << song;
    std::cout << "\n";

    // For real unpredictability, seed from the operating system.
    std::random_device device;
    std::mt19937 unpredictable(device());
    std::cout << "OTP: " << std::uniform_int_distribution<int>(100000, 999999)(unpredictable)
              << " (different every run)\n";
    return 0;
}
