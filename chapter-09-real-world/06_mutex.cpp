// C++ in 199 Pages - 9.6 Mutexes: protecting shared data
// Build: g++ -std=c++17 -pthread 06_mutex.cpp -o mutex && ./mutex

#include <atomic>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

class TicketCounter {
public:
    explicit TicketCounter(int seats) : seatsLeft_(seats) {}

    // Only one thread at a time may check and update seatsLeft_.
    bool book() {
        std::lock_guard<std::mutex> lock(mutex_);   // locks here, unlocks at the closing brace
        if (seatsLeft_ == 0) return false;
        --seatsLeft_;
        return true;
    }

    int seatsLeft() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return seatsLeft_;
    }

private:
    mutable std::mutex mutex_;
    int seatsLeft_;
};

int main() {
    TicketCounter show(100);
    std::atomic<int> booked{0};                  // a simple counter can be atomic instead

    std::vector<std::thread> buyers;
    for (int b = 0; b < 8; ++b) {
        buyers.emplace_back([&show, &booked] {
            for (int attempt = 0; attempt < 20; ++attempt) {   // 8 x 20 = 160 attempts
                if (show.book()) ++booked;
            }
        });
    }
    for (auto& t : buyers) t.join();

    std::cout << "Seats booked: " << booked << "\n";
    std::cout << "Seats left:   " << show.seatsLeft() << "\n";
    std::cout << "Oversold:     " << (booked > 100 ? "yes" : "no") << "\n";
    return 0;
}
