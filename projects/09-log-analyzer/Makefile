SHELL := /bin/bash
CXX ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -pedantic -pthread
SOURCES = src/main.cpp src/analyzer.cpp src/stats.cpp src/log_entry.cpp
HEADERS = src/analyzer.h src/stats.h src/log_entry.h

log_analyzer: $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o log_analyzer

run: log_analyzer
	./log_analyzer --timing logs/*.log

# The golden file uses 4 threads. Every other thread count must give the same
# report, apart from the first line, which names the thread count.
test: log_analyzer
	./log_analyzer --threads 4 logs/*.log > actual_output.txt
	diff -u expected_output.txt actual_output.txt
	for t in 1 2 3 8; do \
	  ./log_analyzer --threads $$t logs/*.log | tail -n +2 | diff -u <(tail -n +2 expected_output.txt) - || exit 1; \
	done
	@echo "Project 9 test passed"

clean:
	rm -f log_analyzer actual_output.txt

.PHONY: run test clean
