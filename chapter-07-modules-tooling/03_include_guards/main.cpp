// C++ in 199 Pages - 7.3 Include guards stop a header being pasted twice.
// Build: g++ -std=c++17 main.cpp -o guards && ./guards
//
// main.cpp includes color.h directly AND through theme.h. Without the guard
// in color.h, struct Color would be defined twice and the build would fail
// with "redefinition of 'struct Color'".

#include <iostream>
#include "color.h"
#include "theme.h"

int main() {
    Theme dark{{18, 18, 18}, {240, 240, 240}};
    Color accent{255, 87, 34};
    std::cout << "Dark theme: background " << toHex(dark.background)
              << ", text " << toHex(dark.text) << "\n";
    std::cout << "Accent colour " << toHex(accent) << "\n";
    return 0;
}
