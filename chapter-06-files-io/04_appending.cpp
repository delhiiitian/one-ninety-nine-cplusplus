// C++ in 199 Pages - 6.4 Appending to a file: a simple log
// Build: g++ -std=c++17 04_appending.cpp -o append && ./append

#include <fstream>
#include <iostream>
#include <string>

void logEvent(const std::string& event) {
    std::ofstream log("events.log", std::ios::app);   // app = add to the end
    log << event << "\n";
}

int countLines(const std::string& path) {
    std::ifstream in(path);
    std::string line;
    int n = 0;
    while (std::getline(in, line)) ++n;
    return n;
}

int main() {
    std::ofstream("events.log").close();    // start fresh for this demo

    logEvent("user=asha action=login");
    logEvent("user=asha action=view_cart");
    logEvent("user=asha action=checkout");
    std::cout << "events.log now has " << countLines("events.log") << " lines\n";

    logEvent("user=ravi action=login");
    std::cout << "After one more event: " << countLines("events.log") << " lines\n";
    return 0;
}
