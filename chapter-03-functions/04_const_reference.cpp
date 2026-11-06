// C++ in 199 Pages - 3.4 const references: fast and safe
// Build: g++ -std=c++17 04_const_reference.cpp -o constref && ./constref

#include <iostream>
#include <string>
#include <vector>

// const& = "look but do not touch". No copy is made, and no change is allowed.
double average(const std::vector<double>& values) {
    double sum = 0.0;
    for (double v : values) {
        sum += v;
    }
    // values.push_back(1.0);   // error: values is read-only here
    return values.empty() ? 0.0 : sum / values.size();
}

int countWords(const std::string& text) {
    int words = 0;
    bool inWord = false;
    for (char c : text) {
        if (c == ' ') {
            inWord = false;
        } else if (!inWord) {
            inWord = true;
            ++words;
        }
    }
    return words;
}

int main() {
    std::vector<double> dailySteps = {8200, 10450, 6300, 12000, 9100, 7600, 11200};
    std::cout << "Average steps: " << average(dailySteps) << "\n";

    std::string review = "Great food  and friendly staff";
    std::cout << "Words in review: " << countWords(review) << "\n";
    return 0;
}
