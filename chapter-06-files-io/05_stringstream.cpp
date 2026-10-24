// C++ in 199 Pages - 6.5 std::stringstream: reading and building text
// Build: g++ -std=c++17 05_stringstream.cpp -o sstream && ./sstream

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int main() {
    // Reading: split a sentence into words and numbers.
    std::istringstream order("3 samosa 2 chai 1 jalebi");
    int qty = 0;
    std::string item;
    int totalItems = 0;
    while (order >> qty >> item) {
        std::cout << "  " << item << " x" << qty << "\n";
        totalItems += qty;
    }
    std::cout << "Total items: " << totalItems << "\n";

    // Splitting on a different character with getline.
    std::istringstream tags("cpp,beginner,books,199");
    std::vector<std::string> parts;
    std::string part;
    while (std::getline(tags, part, ',')) {
        parts.push_back(part);
    }
    std::cout << "Found " << parts.size() << " tags, last is '" << parts.back() << "'\n";

    // Building: assemble text piece by piece, then take the string.
    std::ostringstream msg;
    msg << "Order #" << 1042 << " for " << totalItems << " items is ready";
    std::string sms = msg.str();
    std::cout << sms << " (" << sms.size() << " chars)\n";
    return 0;
}
