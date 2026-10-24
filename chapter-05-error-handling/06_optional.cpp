// C++ in 199 Pages - 5.6 std::optional: a value that might be missing
// Build: g++ -std=c++17 06_optional.cpp -o optional && ./optional

#include <iostream>
#include <map>
#include <optional>
#include <string>

std::optional<std::string> findEmail(const std::map<std::string, std::string>& users,
                                     const std::string& username) {
    auto it = users.find(username);
    if (it == users.end()) {
        return std::nullopt;                 // "no value", not an error
    }
    return it->second;
}

std::optional<int> parsePercent(const std::string& text) {
    if (text.empty() || text.size() > 3) return std::nullopt;
    for (char c : text) {
        if (c < '0' || c > '9') return std::nullopt;
    }
    int value = std::stoi(text);
    if (value > 100) return std::nullopt;
    return value;
}

int main() {
    std::map<std::string, std::string> users = {{"meera", "meera@example.com"}};

    if (auto email = findEmail(users, "meera")) {       // true if it has a value
        std::cout << "Found: " << *email << "\n";
    }
    auto missing = findEmail(users, "omar");
    std::cout << "omar: " << missing.value_or("(no email on file)") << "\n";

    for (const char* input : {"45", "100", "250", "4a", ""}) {
        std::optional<int> p = parsePercent(input);
        std::cout << "\"" << input << "\" -> "
                  << (p ? std::to_string(*p) + "%" : std::string("not a valid percent")) << "\n";
    }
    return 0;
}
