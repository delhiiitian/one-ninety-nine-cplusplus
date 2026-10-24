// C++ in 199 Pages - 5.9 Cleaning up safely: RAII and noexcept
// Build: g++ -std=c++17 09_noexcept_raii.cpp -o raii && ./raii

#include <iostream>
#include <stdexcept>
#include <string>

// A guard object: its destructor runs when it goes out of scope,
// even if an exception is flying past. This pattern is called RAII.
class DoorLock {
public:
    explicit DoorLock(const std::string& room) : room_(room) {
        std::cout << "  [lock " << room_ << "]\n";
    }
    ~DoorLock() {                                  // destructor: always runs
        std::cout << "  [unlock " << room_ << "]\n";
    }
private:
    std::string room_;
};

void useServerRoom(bool somethingBreaks) {
    DoorLock lock("server room");
    std::cout << "  working inside...\n";
    if (somethingBreaks) {
        throw std::runtime_error("power cut");
    }
    std::cout << "  finished normally\n";
}   // lock's destructor runs here in both cases

// noexcept promises this function never throws. Destructors and simple
// getters are good candidates; the compiler can then optimise better.
int add(int a, int b) noexcept {
    return a + b;
}

int main() {
    std::cout << "Normal day:\n";
    useServerRoom(false);

    std::cout << "Bad day:\n";
    try {
        useServerRoom(true);
    } catch (const std::exception& e) {
        std::cout << "  caught: " << e.what() << " (the door was still unlocked)\n";
    }
    std::cout << "2 + 3 = " << add(2, 3) << "\n";
    return 0;
}
