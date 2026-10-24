// C++ in 199 Pages - 6.2 Writing files with std::ofstream
// Build: g++ -std=c++17 02_writing_files.cpp -o write && ./write

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::vector<std::string> tasks = {"Pay electricity bill", "Call plumber",
                                      "Buy birthday gift"};

    std::ofstream out("todo.txt");          // creates the file, or empties it
    if (!out) {                             // always check it opened
        std::cerr << "Could not create todo.txt\n";
        return 1;
    }
    out << "MY TO-DO LIST\n";
    for (std::size_t i = 0; i < tasks.size(); ++i) {
        out << i + 1 << ". " << tasks[i] << "\n";
    }
    out.close();                            // also happens automatically (RAII)

    std::cout << "Wrote " << tasks.size() << " tasks to todo.txt\n";
    return 0;
}
