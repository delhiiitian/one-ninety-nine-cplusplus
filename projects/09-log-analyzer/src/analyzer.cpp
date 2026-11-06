#include "analyzer.h"

#include <algorithm>
#include <fstream>
#include <future>
#include <mutex>
#include <stdexcept>

std::vector<Line> readLines(const std::vector<std::string>& paths) {
    std::vector<Line> lines;
    for (const std::string& path : paths) {
        std::ifstream in(path);
        if (!in) {
            throw std::runtime_error("cannot open " + path);
        }
        // Show only the file name, not the folders, in reports.
        std::string name = path.substr(path.find_last_of("/\\") + 1);
        std::string text;
        int number = 0;
        while (std::getline(in, text)) {
            ++number;
            if (!text.empty() && text.back() == '\r') text.pop_back();   // Windows line endings
            lines.push_back({text, name + ":" + std::to_string(number)});
        }
    }
    return lines;
}

Report analyze(const std::vector<Line>& lines, int threads, std::size_t topN) {
    Report report;
    report.linesRead = static_cast<long long>(lines.size());
    if (threads < 1) threads = 1;
    report.threadsUsed = threads;

    std::mutex malformedMutex;           // guards the one thing all workers share:
    std::vector<std::size_t> malformed;  // positions of lines that did not parse

    // The work for one chunk [from, to). Each worker fills its own Stats,
    // so the counting itself needs no lock.
    auto work = [&](std::size_t from, std::size_t to) {
        Stats local(topN);
        for (std::size_t i = from; i < to; ++i) {
            const Line& line = lines[i];
            if (line.text.empty()) continue;
            if (auto entry = parseLine(line.text)) {
                local.add(*entry, line.where);
            } else {
                std::lock_guard<std::mutex> lock(malformedMutex);
                malformed.push_back(i);
            }
        }
        return local;
    };

    std::vector<std::future<Stats>> futures;
    std::size_t chunk = (lines.size() + threads - 1) / threads;
    for (int t = 0; t < threads; ++t) {
        std::size_t from = std::min(lines.size(), t * chunk);
        std::size_t to = std::min(lines.size(), from + chunk);
        futures.push_back(std::async(std::launch::async, work, from, to));
    }

    report.stats = Stats(topN);
    for (auto& f : futures) {
        report.stats.merge(f.get());   // get() waits, and re-throws any worker exception
    }
    // Threads add malformed lines in any order; sort so the report is repeatable.
    std::sort(malformed.begin(), malformed.end());
    for (std::size_t i : malformed) {
        report.malformed.push_back(lines[i].where + "  " + lines[i].text);
    }
    return report;
}
