CXX ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -pedantic

report_card: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o report_card

run: report_card
	./report_card < sample_input.txt

test: report_card
	./report_card < sample_input.txt > actual_output.txt
	diff -u expected_output.txt actual_output.txt && echo "Project 3 test passed"

clean:
	rm -f report_card actual_output.txt

.PHONY: run test clean
