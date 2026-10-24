// C++ in 199 Pages - 7.4 Namespaces: surnames for your code
// Build: g++ -std=c++17 04_namespaces.cpp -o namespaces && ./namespaces

#include <iostream>
#include <string>

namespace payments {
    double fee(double amount) { return amount * 0.02; }          // 2% card fee
    std::string name() { return "payments"; }
}

namespace shipping {
    double fee(double weightKg) { return 40.0 + weightKg * 15.0; }
    std::string name() { return "shipping"; }

    namespace express {                                            // nested
        double fee(double weightKg) { return 2 * shipping::fee(weightKg); }
    }
}

namespace store::reports {                                         // C++17 nested shorthand
    void print(double total) { std::cout << "Report total: " << total << "\n"; }
}

int main() {
    // Same function name, no clash: the namespace tells them apart.
    double card = payments::fee(2500.0);
    double post = shipping::fee(1.2);
    double fast = shipping::express::fee(1.2);
    std::cout << payments::name() << " fee: " << card << "\n";
    std::cout << shipping::name() << " fee: " << post << ", express: " << fast << "\n";

    namespace rep = store::reports;                                // a short alias
    rep::print(2500.0 + card + post);

    using std::cout;                                               // bring in ONE name
    cout << "using-declarations are fine inside a function.\n";
    // Avoid 'using namespace std;' in headers: it leaks into every file that includes them.
    return 0;
}
