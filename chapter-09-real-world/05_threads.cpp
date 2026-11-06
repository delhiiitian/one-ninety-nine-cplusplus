// C++ in 199 Pages - 9.5 Threads
// Build: g++ -std=c++17 -pthread 05_threads.cpp -o threads && ./threads

#include <iostream>
#include <numeric>
#include <thread>
#include <vector>

// Each worker sums its own slice and writes into its own slot: no sharing.
void sumSlice(const std::vector<int>& data, std::size_t from, std::size_t to, long long& result) {
    result = std::accumulate(data.begin() + from, data.begin() + to, 0LL);
}

int main() {
    std::vector<int> sales(1'000'000);
    std::iota(sales.begin(), sales.end(), 1);   // 1, 2, 3, ..., 1,000,000

    unsigned cores = std::thread::hardware_concurrency();
    std::cout << "Hardware threads on this machine: " << cores << "\n";   // 0 means unknown

    const std::size_t workers = 4;
    std::vector<long long> partial(workers, 0);
    std::vector<std::thread> threads;

    std::size_t chunk = sales.size() / workers;
    for (std::size_t w = 0; w < workers; ++w) {
        std::size_t from = w * chunk;
        std::size_t to = (w == workers - 1) ? sales.size() : from + chunk;
        // std::cref and std::ref pass references into the new thread.
        threads.emplace_back(sumSlice, std::cref(sales), from, to, std::ref(partial[w]));
    }

    for (std::thread& t : threads) t.join();   // wait for every worker to finish

    for (std::size_t w = 0; w < workers; ++w) {
        std::cout << "Worker " << w << " sum: " << partial[w] << "\n";
    }
    long long total = std::accumulate(partial.begin(), partial.end(), 0LL);
    std::cout << "Total: " << total << "\n";
    std::cout << "Check: " << (total == 1'000'000LL * 1'000'001LL / 2 ? "correct" : "wrong") << "\n";
    return 0;
}
