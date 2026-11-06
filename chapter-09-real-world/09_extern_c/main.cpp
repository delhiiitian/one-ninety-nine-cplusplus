// C++ in 199 Pages - 9.9 Calling C code with extern "C"
// Build: gcc -c legacy_tax.c && g++ -std=c++17 main.cpp legacy_tax.o -o bill && ./bill

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include "legacy_tax.h"   // a C header, safe to include thanks to its extern "C" block

// A C++ helper that wraps the C buffer API in a std::string.
std::string rupees(long paise) {
    char buffer[32];
    format_rupees(paise, buffer, sizeof buffer);
    return buffer;
}

// A function with C linkage, so C code (here, qsort) can call back into C++.
extern "C" int comparePaise(const void* a, const void* b) {
    long x = *static_cast<const long*>(a);
    long y = *static_cast<const long*>(b);
    return (x > y) - (x < y);
}

int main() {
    struct Item { std::string name; long pricePaise; int gstRate; };
    std::vector<Item> cart{{"Notebook", 12000, 12}, {"Headphones", 149900, 18}, {"Rice 5kg", 42500, 5}};

    std::vector<long> totals;
    for (const Item& item : cart) {
        long tax = gst_paise(item.pricePaise, item.gstRate);   // calling C from C++
        totals.push_back(item.pricePaise + tax);
        std::cout << item.name << ": " << rupees(item.pricePaise) << " + GST " << item.gstRate
                  << "% " << rupees(tax) << " = " << rupees(item.pricePaise + tax) << "\n";
    }

    std::qsort(totals.data(), totals.size(), sizeof(long), comparePaise);   // C library sort
    std::cout << "Cheapest line: " << rupees(totals.front()) << "\n";
    std::cout << "Dearest line:  " << rupees(totals.back()) << "\n";
    return 0;
}
