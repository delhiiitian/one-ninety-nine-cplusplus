// C++ in 199 Pages - 7.7 Debugging: logging and the debugger
// Build (normal): g++ -std=c++17 07_debugging.cpp -o debug && ./debug
// Build (debug):  g++ -std=c++17 -g -DDEBUG_LOGGING 07_debugging.cpp -o debug && ./debug
// Debugger:       gdb ./debug   then: break discountedTotal, run, next, print subtotal

#include <iostream>
#include <vector>

// A logging macro that adds the file and line, and disappears in normal builds.
#ifdef DEBUG_LOGGING
#define LOG(msg) (std::cerr << "[" << __FILE__ << ":" << __LINE__ << "] " << msg << "\n")
#else
#define LOG(msg) ((void)0)
#endif

double discountedTotal(const std::vector<double>& prices, double discountPercent) {
    double subtotal = 0.0;
    for (double p : prices) {
        subtotal += p;
        LOG("added " << p << ", subtotal now " << subtotal);
    }
    double discount = subtotal * discountPercent / 100.0;
    LOG("discount " << discount);
    return subtotal - discount;
}

int main() {
    std::vector<double> cart = {499.0, 1299.0, 249.0};
    double total = discountedTotal(cart, 10);
    std::cout << "Total after 10% discount: " << total << "\n";

    // A quick "print debugging" check, written to stderr so it never mixes
    // with the real output if you redirect it to a file.
    std::cerr << "debug: cart has " << cart.size() << " items\n";
    return 0;
}
