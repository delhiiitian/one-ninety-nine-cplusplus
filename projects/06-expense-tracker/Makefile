CXX ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -pedantic

expense_tracker: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o expense_tracker

run: expense_tracker
	./expense_tracker

# Two separate runs prove the data survives between sessions.
test: expense_tracker
	rm -rf data
	./expense_tracker < session1.txt > actual_output.txt
	./expense_tracker < session2.txt >> actual_output.txt
	cat data/report-2026-10.txt >> actual_output.txt
	diff -u expected_output.txt actual_output.txt && echo "Project 6 test passed"
	rm -rf data

clean:
	rm -rf expense_tracker actual_output.txt data

.PHONY: run test clean
