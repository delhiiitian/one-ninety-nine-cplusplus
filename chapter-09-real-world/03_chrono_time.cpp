// C++ in 199 Pages - 9.3 Time and durations with <chrono>
// Build: g++ -std=c++17 03_chrono_time.cpp -o timing && ./timing

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <thread>

using namespace std::chrono_literals;   // lets us write 90min, 250ms, 2h

int main() {
    // 1. Durations: a typed amount of time. The type stops unit mix-ups.
    std::chrono::minutes movie = 2h + 45min;
    std::cout << "Movie length: " << movie.count() << " minutes\n";
    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(movie);
    std::cout << "That is " << seconds.count() << " seconds\n";

    // 2. Measuring how long something takes: use steady_clock.
    auto start = std::chrono::steady_clock::now();
    std::this_thread::sleep_for(120ms);           // pretend to do some work
    auto elapsed = std::chrono::steady_clock::now() - start;
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
    std::cout << "Work took about " << (ms / 10) * 10 << " ms\n";   // rounded to 10 ms

    // 3. Wall-clock time: system_clock, converted to a calendar date for printing.
    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::tm utc = *std::gmtime(&t);
    std::cout << "Current year (UTC): " << utc.tm_year + 1900 << "\n";

    // 4. Deadlines: a time point plus a duration.
    auto deadline = now + 48h;
    auto hoursLeft = std::chrono::duration_cast<std::chrono::hours>(deadline - now).count();
    std::cout << "Hours until the deadline: " << hoursLeft << "\n";

    // 5. Formatting a fixed date the same way a log file would.
    std::tm launch{};
    launch.tm_year = 2025 - 1900; launch.tm_mon = 0; launch.tm_mday = 26;
    launch.tm_hour = 9; launch.tm_min = 30;
    std::cout << "Launch: " << std::put_time(&launch, "%Y-%m-%d %H:%M") << "\n";
    return 0;
}
