// C++ in 199 Pages - Project 9: Parallel Log Analyzer
// Uses Chapter 9 ideas: command-line arguments, environment variables,
// <chrono>, threads, a mutex, std::async, regex, plus files from Chapter 6.
//
// Usage: log_analyzer [--threads N] [--top N] [--timing] FILE...
// The default thread count comes from LOG_ANALYZER_THREADS, or the CPU count.
//
// Build: make        Test: make test

#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <thread>
#include <vector>

#include "analyzer.h"

struct Options {
    int threads = 0;
    std::size_t top = 5;
    bool timing = false;
    std::vector<std::string> files;
};

int defaultThreads() {
    if (const char* env = std::getenv("LOG_ANALYZER_THREADS")) {
        return std::max(1, std::atoi(env));
    }
    unsigned cores = std::thread::hardware_concurrency();
    return cores == 0 ? 2 : static_cast<int>(cores);
}

Options parseArgs(int argc, char* argv[]) {
    Options opts;
    opts.threads = defaultThreads();
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--timing") {
            opts.timing = true;
        } else if (arg == "--threads" || arg == "--top") {
            if (i + 1 >= argc) throw std::invalid_argument(arg + " needs a number");
            int value = std::stoi(argv[++i]);
            if (value < 1) throw std::invalid_argument(arg + " must be at least 1");
            if (arg == "--threads") opts.threads = value;
            else opts.top = static_cast<std::size_t>(value);
        } else if (arg.rfind("--", 0) == 0) {
            throw std::invalid_argument("unknown option " + arg);
        } else {
            opts.files.push_back(arg);
        }
    }
    if (opts.files.empty()) throw std::invalid_argument("give at least one log file");
    return opts;
}

void printReport(const Report& r, std::size_t files) {
    const Stats& s = r.stats;
    std::cout << "Analysed " << r.linesRead << " lines from " << files << " file(s) on "
              << r.threadsUsed << " thread(s)\n";
    std::cout << "Parsed entries: " << s.entries() << ", malformed: " << r.malformed.size() << "\n";
    for (const std::string& bad : r.malformed) std::cout << "  ? " << bad << "\n";

    std::cout << "\nEntries by level\n";
    for (const std::string level : {"DEBUG", "INFO", "WARN", "ERROR"}) {
        auto it = s.byLevel().find(level);
        long long n = it == s.byLevel().end() ? 0 : it->second;
        std::cout << "  " << std::left << std::setw(6) << level << std::right << std::setw(5) << n
                  << "  " << std::string(static_cast<std::size_t>((n + 4) / 5), '#') << "\n";
    }

    std::cout << "\nErrors by service\n";
    for (const auto& [service, n] : s.errorsByService()) {
        std::cout << "  " << std::left << std::setw(10) << service << std::right << std::setw(3) << n << "\n";
    }

    std::cout << "\nErrors by hour\n";
    for (const auto& [hour, n] : s.errorsByHour()) {
        std::cout << "  " << std::setw(2) << std::setfill('0') << hour << ":00" << std::setfill(' ')
                  << std::setw(4) << n << "\n";
    }

    std::cout << "\nAverage response time: " << std::fixed << std::setprecision(1) << s.averageMs()
              << " ms\n";
    std::cout << "Slowest " << s.slowest().size() << " requests\n";
    for (const SlowRequest& req : s.slowest()) {
        std::cout << "  " << std::setw(5) << req.durationMs << " ms  " << std::left << std::setw(15)
                  << req.where << std::setw(10) << req.service << std::right << req.message << "\n";
    }
}

int main(int argc, char* argv[]) {
    try {
        Options opts = parseArgs(argc, argv);
        auto start = std::chrono::steady_clock::now();

        std::vector<Line> lines = readLines(opts.files);
        Report report = analyze(lines, opts.threads, opts.top);
        printReport(report, opts.files.size());

        if (opts.timing) {   // off by default so the test output never changes
            auto us = std::chrono::duration_cast<std::chrono::microseconds>(
                          std::chrono::steady_clock::now() - start).count();
            std::cout << "\nTook " << us << " microseconds\n";
        }
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "log_analyzer: " << e.what() << "\n"
                  << "Usage: log_analyzer [--threads N] [--top N] [--timing] FILE...\n";
        return 1;
    }
}
