// C++ in 199 Pages - Project 9: Parallel Log Analyzer
// stats.h - the totals one worker collects, and how to combine two of them.
#pragma once

#include <map>
#include <string>
#include <vector>

#include "log_entry.h"

struct SlowRequest {
    int durationMs = 0;
    std::string where;     // "web-02.log:41"
    std::string service;
    std::string message;
};

class Stats {
public:
    explicit Stats(std::size_t keepSlowest = 5) : keepSlowest_(keepSlowest) {}

    void add(const LogEntry& entry, const std::string& where);
    void merge(const Stats& other);   // used after the threads finish

    long long entries() const { return entries_; }
    const std::map<std::string, long long>& byLevel() const { return byLevel_; }
    const std::map<std::string, long long>& errorsByService() const { return errorsByService_; }
    const std::map<int, long long>& errorsByHour() const { return errorsByHour_; }
    const std::vector<SlowRequest>& slowest() const { return slowest_; }
    double averageMs() const { return timed_ == 0 ? 0.0 : static_cast<double>(totalMs_) / timed_; }

private:
    void keepIfSlow(const SlowRequest& request);

    std::size_t keepSlowest_;
    long long entries_ = 0;
    long long timed_ = 0;
    long long totalMs_ = 0;
    std::map<std::string, long long> byLevel_;
    std::map<std::string, long long> errorsByService_;
    std::map<int, long long> errorsByHour_;
    std::vector<SlowRequest> slowest_;   // sorted, slowest first
};
