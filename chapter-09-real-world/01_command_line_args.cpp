// C++ in 199 Pages - 9.1 Command-line arguments
// Build: g++ -std=c++17 01_command_line_args.cpp -o greet
// Run:   ./greet --name Asha --times 2 --shout

#include <cctype>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

struct Options {
    std::string name = "world";
    int times = 1;
    bool shout = false;
};

Options parseArgs(const std::vector<std::string>& args) {
    Options opts;
    for (std::size_t i = 0; i < args.size(); ++i) {
        const std::string& arg = args[i];
        if (arg == "--shout") {
            opts.shout = true;
        } else if ((arg == "--name" || arg == "--times") && i + 1 < args.size()) {
            const std::string& value = args[++i];          // the next word is the value
            if (arg == "--name") opts.name = value;
            else opts.times = std::stoi(value);
        } else {
            throw std::invalid_argument("unknown or incomplete option: " + arg);
        }
    }
    return opts;
}

int main(int argc, char* argv[]) {
    std::cout << "Program name: " << argv[0] << "\n";
    std::cout << "Arguments given: " << argc - 1 << "\n";

    // argv[1] .. argv[argc - 1] are the words typed after the program name.
    std::vector<std::string> args(argv + 1, argv + argc);

    // With no arguments, show what a typical command line would produce.
    if (args.empty()) {
        std::cout << "(none given, using a demo: --name Asha --times 2 --shout)\n";
        args = {"--name", "Asha", "--times", "2", "--shout"};
    }

    try {
        Options opts = parseArgs(args);
        std::string greeting = "Hello, " + opts.name + "!";
        if (opts.shout) {
            for (char& c : greeting) c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
        }
        for (int i = 0; i < opts.times; ++i) std::cout << greeting << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Usage: greet [--name NAME] [--times N] [--shout]\n" << e.what() << "\n";
        return 1;   // a non-zero exit code tells scripts that something went wrong
    }
    return 0;
}
