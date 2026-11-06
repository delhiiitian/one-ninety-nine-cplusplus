// C++ in 199 Pages - 2.3 switch
// Build: g++ -std=c++17 03_switch.cpp -o switch && ./switch
// Try:   echo 2 | ./switch

#include <iostream>

int main() {
    std::cout << "Coffee machine\n";
    std::cout << "1) Espresso  2) Cappuccino  3) Latte  4) Hot water\n";
    std::cout << "Choose: ";
    int choice = 0;
    std::cin >> choice;

    switch (choice) {
        case 1:
            std::cout << "\nEspresso: 90 rupees\n";
            break;                          // stop here, skip the other cases
        case 2:
        case 3:                             // two cases share one block
            std::cout << "\nMilk coffee: 140 rupees\n";
            break;
        case 4:
            std::cout << "\nHot water is free\n";
            break;
        default:                            // anything not listed above
            std::cout << "\nUnknown button\n";
            break;
    }
    return 0;
}
