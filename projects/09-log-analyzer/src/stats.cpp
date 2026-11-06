#include "stats.h"

#include <algorithm>

void Stats::add(const LogEntry& entry, const std::string& where) {
    ++entries_;
    ++byLevel_[entry.level];
    if (entry.level == "ERROR") {
        ++errorsByService_[entry.service];
        ++errorsByHour_[entry.hour];
    }
    if (entry.durationMs) {
        ++timed_;
        totalMs_ += *entry.durationMs;
        keepIfSlow({*entry.durationMs, where, entry.service, entry.message});
    }
}

void Stats::merge(const Stats& other) {
    entries_ += other.entries_;
    timed_ += other.timed_;
    totalMs_ += other.totalMs_;
    for (const auto& [level, n] : other.byLevel_) byLevel_[level] += n;
    for (const auto& [service, n] : other.errorsByService_) errorsByService_[service] += n;
    for (const auto& [hour, n] : other.errorsByHour_) errorsByHour_[hour] += n;
    for (const SlowRequest& r : other.slowest_) keepIfSlow(r);
}

// Keep only the N slowest. Ties are broken by location so the result never
// depends on which thread finished first.
void Stats::keepIfSlow(const SlowRequest& request) {
    slowest_.push_back(request);
    std::sort(slowest_.begin(), slowest_.end(), [](const SlowRequest& a, const SlowRequest& b) {
        if (a.durationMs != b.durationMs) return a.durationMs > b.durationMs;
        return a.where < b.where;
    });
    if (slowest_.size() > keepSlowest_) slowest_.resize(keepSlowest_);
}
