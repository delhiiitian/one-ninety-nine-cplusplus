#include "log_entry.h"

#include <regex>

std::optional<LogEntry> parseLine(const std::string& line) {
    // date time LEVEL [service] message, optionally ending in " in 123ms".
    // static: the pattern is compiled once and shared (reading it from many threads is safe).
    static const std::regex pattern(
        R"(^(\d{4}-\d{2}-\d{2}) ((\d{2}):\d{2}:\d{2}) (DEBUG|INFO|WARN|ERROR) \[([a-z-]+)\] (.*?)(?: in (\d+)ms)?$)");

    std::smatch m;
    if (!std::regex_match(line, m, pattern)) {
        return std::nullopt;
    }
    LogEntry e;
    e.date = m[1];
    e.time = m[2];
    e.hour = std::stoi(m[3]);
    e.level = m[4];
    e.service = m[5];
    e.message = m[6];
    if (m[7].matched) {
        e.durationMs = std::stoi(m[7]);
    }
    return e;
}
