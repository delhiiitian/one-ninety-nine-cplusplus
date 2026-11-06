// C++ in 199 Pages - 9.8 Regular expressions
// Build: g++ -std=c++17 08_regex.cpp -o regex && ./regex

#include <iostream>
#include <regex>
#include <string>
#include <vector>

int main() {
    // 1. Validate: does the whole string match? (Indian PIN code: 6 digits, not starting with 0)
    std::regex pin(R"([1-9][0-9]{5})");
    for (std::string code : {"560001", "056001", "56001"}) {
        std::cout << code << (std::regex_match(code, pin) ? " is" : " is not") << " a valid PIN\n";
    }

    // 2. Capture: pull pieces out with groups ( ).
    std::regex logLine(R"((\d{2}:\d{2}:\d{2}) (INFO|WARN|ERROR) (.*))");
    std::string line = "14:05:09 ERROR payment timeout for order 8812";
    std::smatch m;
    if (std::regex_match(line, m, logLine)) {
        std::cout << "time=" << m[1] << " level=" << m[2] << " message=\"" << m[3] << "\"\n";
    }

    // 3. Search: find every match inside a longer text.
    std::string text = "Call 98450 12345 or 080 2222 3333, or mail help@shop.in";
    std::regex email(R"([\w.]+@[\w.]+\.\w+)");
    std::regex numberGroup(R"(\d+)");
    std::vector<std::string> numbers;
    for (std::sregex_iterator it(text.begin(), text.end(), numberGroup), end; it != end; ++it) {
        numbers.push_back(it->str());
    }
    std::cout << "Number groups found: " << numbers.size() << "\n";
    if (std::regex_search(text, m, email)) std::cout << "Email found: " << m.str() << "\n";

    // 4. Replace: mask all but the last 4 digits of a card number.
    std::string card = "4111 1111 1111 1234";
    std::cout << "Masked: " << std::regex_replace(card, std::regex(R"(\d{4} )"), "**** ") << "\n";
    return 0;
}
