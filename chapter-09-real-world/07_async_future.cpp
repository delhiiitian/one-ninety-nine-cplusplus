// C++ in 199 Pages - 9.7 async and future: tasks that return results
// Build: g++ -std=c++17 -pthread 07_async_future.cpp -o async && ./async

#include <chrono>
#include <future>
#include <iostream>
#include <stdexcept>
#include <string>
#include <thread>

using namespace std::chrono_literals;

// Pretend these are slow network calls to three different services.
int fetchPrice(const std::string& item) {
    std::this_thread::sleep_for(100ms);
    if (item == "laptop") return 55000;
    if (item == "phone") return 18000;
    throw std::runtime_error("no price for " + item);
}

int fetchStock(const std::string&) {
    std::this_thread::sleep_for(100ms);
    return 12;
}

int main() {
    auto start = std::chrono::steady_clock::now();

    // std::launch::async starts each call on its own thread right away.
    std::future<int> price = std::async(std::launch::async, fetchPrice, "laptop");
    std::future<int> stock = std::async(std::launch::async, fetchStock, "laptop");

    // get() waits for the result. Both calls ran at the same time.
    std::cout << "Laptop price: Rs " << price.get() << "\n";
    std::cout << "In stock:     " << stock.get() << "\n";

    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                  std::chrono::steady_clock::now() - start).count();
    std::cout << "Both answers in under 190 ms: " << (ms < 190 ? "yes" : "no") << "\n";

    // An exception thrown inside the task comes back out of get().
    std::future<int> missing = std::async(std::launch::async, fetchPrice, "spaceship");
    try {
        std::cout << missing.get() << "\n";
    } catch (const std::exception& e) {
        std::cout << "Error from task: " << e.what() << "\n";
    }
    return 0;
}
