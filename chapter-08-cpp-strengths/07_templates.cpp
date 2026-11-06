// C++ in 199 Pages - 8.7 Templates: write once, use with any type
// Build: g++ -std=c++17 07_templates.cpp -o templates && ./templates

#include <iostream>
#include <string>
#include <vector>

// A function template: T is filled in by the compiler for each type you use.
template <typename T>
T largest(const std::vector<T>& items) {
    T best = items.at(0);
    for (const T& item : items) {
        if (best < item) best = item;
    }
    return best;
}

// A class template: a fixed-size "recently used" list for any type.
template <typename T, std::size_t Capacity>
class RecentList {
public:
    void add(const T& item) {
        items_.insert(items_.begin(), item);       // newest first
        if (items_.size() > Capacity) items_.pop_back();
    }
    void print(const std::string& title) const {
        std::cout << title << ":";
        for (const T& item : items_) std::cout << " " << item;
        std::cout << "\n";
    }
private:
    std::vector<T> items_;
};

int main() {
    std::cout << "Largest int: " << largest(std::vector<int>{4, 19, 7}) << "\n";
    std::cout << "Largest price: " << largest(std::vector<double>{99.5, 250.0, 12.75}) << "\n";
    std::cout << "Last name alphabetically: "
              << largest(std::vector<std::string>{"Neha", "Arun", "Zoya", "Imran"}) << "\n";

    RecentList<std::string, 3> recentFiles;
    for (const char* f : {"budget.xlsx", "photo.jpg", "notes.txt", "song.mp3"}) {
        recentFiles.add(f);
    }
    recentFiles.print("Recent files");

    RecentList<int, 2> recentPins;
    recentPins.add(411001);
    recentPins.add(560001);
    recentPins.add(110001);
    recentPins.print("Recent PIN codes");
    // std::vector<int>, std::map<K, V> and std::unique_ptr<T> are all templates too.
    return 0;
}
