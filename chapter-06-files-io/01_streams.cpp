// C++ in 199 Pages - 6.1 Streams: one idea for screen, files and text
// Build: g++ -std=c++17 01_streams.cpp -o streams && ./streams

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

// This function writes a greeting to ANY output stream.
void writeGreeting(std::ostream& out, const std::string& name) {
    out << "Hello, " << name << "! Your order is on its way.\n";
}

int main() {
    writeGreeting(std::cout, "Kiran");             // to the screen

    std::ofstream file("greeting.txt");            // to a file
    writeGreeting(file, "Kiran");
    file.close();

    std::ostringstream text;                       // to a string in memory
    writeGreeting(text, "Kiran");
    std::cout << "Captured " << text.str().size() << " characters in memory\n";

    std::cerr << "This line goes to the error stream (stderr)\n";
    std::cout << "Check greeting.txt: it holds the same sentence.\n";
    return 0;
}
