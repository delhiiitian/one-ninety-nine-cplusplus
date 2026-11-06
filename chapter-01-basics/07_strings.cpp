// C++ in 199 Pages - 1.7 Strings
// Build: g++ -std=c++17 07_strings.cpp -o strings && ./strings

#include <iostream>
#include <string>

int main() {
    std::string first = "Ada";
    std::string last  = "Lovelace";
    std::string full  = first + " " + last;          // join with +

    std::cout << "Full name: " << full << "\n";
    std::cout << "Length: " << full.size() << " characters\n";
    std::cout << "First letter: " << full[0] << "\n";
    std::cout << "Surname from position 4: " << full.substr(4) << "\n";

    std::size_t pos = full.find("Love");             // search inside
    if (pos != std::string::npos) {
        std::cout << "'Love' found at index " << pos << "\n";
    }

    full.replace(0, 3, "Augusta Ada");               // edit in place
    std::cout << "Updated: " << full << "\n";

    std::string email = "ada@example.com";
    std::string user = email.substr(0, email.find('@'));
    std::cout << "Username part of email: " << user << "\n";
    return 0;
}
