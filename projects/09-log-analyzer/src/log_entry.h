// C++ in 199 Pages - Project 9: Parallel Log Analyzer
// log_entry.h - one parsed line of a log file (lesson 9.8: regex).
#pragma once

#include <optional>
#include <string>

struct LogEntry {
    std::string date;          // 2025-03-14
    std::string time;          // 09:15:02
    int hour = 0;              // 9
    std::string level;         // DEBUG, INFO, WARN or ERROR
    std::string service;       // checkout, payments, ...
    std::string message;       // order placed
    std::optional<int> durationMs;   // present when the line ends with "in 184ms"
};

// Returns the parsed entry, or nothing if the line does not match the format.
std::optional<LogEntry> parseLine(const std::string& line);
