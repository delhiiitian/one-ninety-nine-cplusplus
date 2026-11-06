// C++ in 199 Pages - 4.4 std::map: look things up by key, kept in order
// Build: g++ -std=c++17 04_map.cpp -o map && ./map

#include <iostream>
#include <map>
#include <string>

int main() {
    std::map<std::string, std::string> phoneBook;
    phoneBook["Ravi"]  = "98100 11111";
    phoneBook["Anita"] = "98200 22222";
    phoneBook["Zubin"] = "98300 33333";
    phoneBook.insert({"Bela", "98400 44444"});

    std::cout << "Anita: " << phoneBook["Anita"] << "\n";

    // find() checks without accidentally adding a new entry.
    auto it = phoneBook.find("Karan");
    if (it == phoneBook.end()) {
        std::cout << "Karan is not in the phone book\n";
    }
    if (phoneBook.count("Ravi") > 0) {
        std::cout << "Ravi is saved\n";
    }

    phoneBook.erase("Zubin");

    // A map is always sorted by key: alphabetical here.
    for (const auto& [name, number] : phoneBook) {    // structured binding
        std::cout << name << " -> " << number << "\n";
    }

    // Counting with a map: how many times does each word appear?
    std::map<std::string, int> votes;
    std::string ballot[] = {"tea", "coffee", "tea", "juice", "tea", "coffee"};
    for (const std::string& v : ballot) {
        ++votes[v];                       // missing keys start at 0
    }
    for (const auto& [drink, count] : votes) {
        std::cout << drink << ": " << count << "\n";
    }
    return 0;
}
