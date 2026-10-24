// C++ in 199 Pages - 7.3 A classic include guard.
#ifndef ONE_NINETY_NINE_COLOR_H
#define ONE_NINETY_NINE_COLOR_H

#include <string>

struct Color {
    int r, g, b;
};

inline std::string toHex(const Color& c) {
    const char* digits = "0123456789ABCDEF";
    std::string hex = "#";
    for (int part : {c.r, c.g, c.b}) {
        hex += digits[part / 16];
        hex += digits[part % 16];
    }
    return hex;
}

#endif  // ONE_NINETY_NINE_COLOR_H
