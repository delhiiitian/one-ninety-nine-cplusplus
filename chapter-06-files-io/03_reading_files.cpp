// C++ in 199 Pages - 6.3 Reading files line by line with std::ifstream
// Build: g++ -std=c++17 03_reading_files.cpp -o read && ./read

#include <fstream>
#include <iostream>
#include <string>

int main() {
    // Create a small file first so this example works on its own.
    {
        std::ofstream setup("poem.txt");
        setup << "Where the mind is without fear\n"
              << "and the head is held high\n"
              << "\n"
              << "Where knowledge is free\n";
    }   // setup closes here

    std::ifstream in("poem.txt");
    if (!in) {
        std::cerr << "Could not open poem.txt\n";
        return 1;
    }

    std::string line;
    int lineNumber = 0;
    int words = 0;
    while (std::getline(in, line)) {          // false at end of file
        ++lineNumber;
        if (line.empty()) {
            continue;
        }
        std::cout << lineNumber << ": " << line << "\n";
        for (std::size_t i = 0; i < line.size(); ++i) {
            if (line[i] != ' ' && (i == 0 || line[i - 1] == ' ')) ++words;
        }
    }
    std::cout << lineNumber << " lines, " << words << " words\n";

    std::ifstream missing("no_such_file.txt");
    std::cout << "Opening a missing file " << (missing ? "worked" : "failed, as expected") << "\n";
    return 0;
}
