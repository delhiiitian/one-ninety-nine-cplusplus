// C++ in 199 Pages - 1.8 Type conversion
// Build: g++ -std=c++17 08_type_conversion.cpp -o convert && ./convert

#include <iostream>
#include <string>

int main() {
    int totalMarks = 437;
    int subjects = 5;

    double wrong = totalMarks / subjects;                        // 87 (int division first)
    double right = static_cast<double>(totalMarks) / subjects;   // 87.4
    std::cout << "Average (wrong): " << wrong << "\n";
    std::cout << "Average (right): " << right << "\n";

    double price = 99.99;
    int rupees = static_cast<int>(price);        // drops the decimals: 99
    std::cout << "Whole rupees: " << rupees << "\n";

    // Text <-> numbers
    std::string ageText = "42";
    int age = std::stoi(ageText);                 // string to int
    double temp = std::stod("36.6");              // string to double
    std::string label = "Age next year: " + std::to_string(age + 1);
    std::cout << label << ", temperature " << temp << "\n";

    char letter = 'A';
    std::cout << "'A' is stored as the number " << static_cast<int>(letter) << "\n";
    return 0;
}
