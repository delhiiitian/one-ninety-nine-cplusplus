// C++ in 199 Pages - Project 9: Parallel Log Analyzer
// analyzer.h - reads log files and analyses them on several threads.
#pragma once

#include <string>
#include <vector>

#include "stats.h"

struct Line {
    std::string text;
    std::string where;   // "file.log:12"
};

struct Report {
    Stats stats;
    long long linesRead = 0;
    std::vector<std::string> malformed;   // "file.log:18  <the line>"
    int threadsUsed = 0;
};

// Reads every line of every file. Throws std::runtime_error if a file cannot be opened.
std::vector<Line> readLines(const std::vector<std::string>& paths);

// Splits the lines into one chunk per thread, analyses the chunks at the same
// time with std::async, then merges the results.
Report analyze(const std::vector<Line>& lines, int threads, std::size_t topN);
