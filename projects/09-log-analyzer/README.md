# Project 9: Parallel Log Analyzer

Reads web-server log files, splits the lines across several threads, and
prints a health report: entries per level, errors per service and per hour,
the average response time and the slowest requests. Lines that do not match
the log format are listed so nothing is silently lost.

It uses Chapter 9 ideas: command-line arguments, an environment variable,
`<chrono>`, `std::async` and futures, a `std::mutex`, and `<regex>`, plus file
reading from Chapter 6 and classes from Chapter 8.

## Log format

```
2025-03-14 09:15:02 INFO [checkout] order placed in 184ms
```

Date, time, level (`DEBUG`, `INFO`, `WARN` or `ERROR`), service in square
brackets, a message, and an optional `in <n>ms` response time.

## Usage

```
log_analyzer [--threads N] [--top N] [--timing] FILE...
```

| Option | Meaning |
| --- | --- |
| `--threads N` | number of worker threads (default: `LOG_ANALYZER_THREADS`, or the CPU count) |
| `--top N` | how many slow requests to list (default 5) |
| `--timing` | also print how long the analysis took |

## Files

| File | What it is |
| --- | --- |
| `src/log_entry.h`, `src/log_entry.cpp` | `LogEntry` and `parseLine`, the regex that reads one line |
| `src/stats.h`, `src/stats.cpp` | `Stats`: the counts one worker collects, and `merge` to combine them |
| `src/analyzer.h`, `src/analyzer.cpp` | `readLines` and `analyze`, which runs the workers with `std::async` |
| `src/main.cpp` | options, environment variable, timing and the printed report |
| `logs/web-01.log` ... `web-03.log` | sample logs from three servers, with a few broken lines |
| `expected_output.txt` | the report for the sample logs |
| `Makefile`, `CMakeLists.txt` | build with Make or CMake |

## Run it

```sh
make run      # analyse the sample logs and show the time taken
make test     # compare with expected_output.txt, then check that 1, 2, 3 and 8 threads agree
LOG_ANALYZER_THREADS=2 ./log_analyzer logs/*.log
```
