// C++ in 199 Pages - 4.6 std::set: unique items, kept sorted
// Build: g++ -std=c++17 06_set.cpp -o set && ./set

#include <iostream>
#include <set>
#include <string>

int main() {
    // Guest list: adding the same person twice has no effect.
    std::set<std::string> guests;
    guests.insert("Priya");
    guests.insert("Arjun");
    guests.insert("Priya");          // duplicate, ignored
    guests.insert("Dev");

    std::cout << "Guests (" << guests.size() << "): ";
    for (const auto& g : guests) {
        std::cout << g << " ";        // alphabetical
    }
    std::cout << "\n";

    std::cout << "Is Arjun invited? " << (guests.count("Arjun") ? "yes" : "no") << "\n";

    // Unique visitors from a log full of repeats
    int visitorIds[] = {104, 101, 104, 103, 101, 104, 102};
    std::set<int> unique(std::begin(visitorIds), std::end(visitorIds));
    std::cout << "Visits: 7, unique visitors: " << unique.size()
              << ", lowest id: " << *unique.begin() << "\n";
    return 0;
}
