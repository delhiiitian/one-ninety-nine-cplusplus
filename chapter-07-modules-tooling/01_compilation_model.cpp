// C++ in 199 Pages - 7.1 How C++ is built: preprocess, compile, link
// Build: g++ -std=c++17 01_compilation_model.cpp -o build_steps && ./build_steps
//
// See each stage yourself:
//   g++ -std=c++17 -E 01_compilation_model.cpp -o expanded.ii   # 1. preprocess only
//   g++ -std=c++17 -c 01_compilation_model.cpp -o step.o        # 2. compile to object code
//   g++ step.o -o build_steps                                   # 3. link into a program

#include <iostream>   // the preprocessor pastes the whole <iostream> header here

// #define is a preprocessor instruction: plain text replacement before compiling.
#define APP_NAME "Build Demo"
#define SQUARE(x) ((x) * (x))     // a macro "function"; prefer real functions

// Conditional compilation: code included only when a name is defined.
#define SHOW_DETAILS

int main() {
    std::cout << APP_NAME << "\n";
    std::cout << "SQUARE(7) = " << SQUARE(7) << "\n";

#ifdef SHOW_DETAILS
    std::cout << "Compiled from " << __FILE__ << " on line " << __LINE__ << "\n";
    std::cout << "C++ standard version: " << __cplusplus << "\n";
#endif

#ifdef _WIN32
    std::cout << "Built for Windows\n";
#else
    std::cout << "Built for a Unix-like system (Linux or macOS)\n";
#endif
    return 0;
}
