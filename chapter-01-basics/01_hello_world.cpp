// C++ in 199 Pages - 1.1 Hello, World
// Build: g++ -std=c++17 01_hello_world.cpp -o hello && ./hello
//
// Every C++ program starts running at main(). This file shows the smallest
// useful program: include a library, write main, print text, return 0.

#include <iostream>   // gives us std::cout for printing

int main() {
    std::cout << "Hello, World!\n";          // print one line
    std::cout << "Welcome to C++ in 199 Pages.\n";
    return 0;                                // 0 tells the OS "all good"
}
